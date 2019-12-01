#include "Playing.hpp"

bool Playing::should_pause_sounds = false;

Playing::Playing(sf::RenderWindow& w, StateManager& sm) : State(w, sm), SoundMaking(20)
{
	main_bg = new Background(0.06f, { 171.f, 0 }, "background");
	layer1 = new Background(0.04f, { 171.f, 0 }, "layer1");

	for (int i = 1; i <= 2; i++)
		levels.push_back(new Level(i));

	std::vector<Alien*> temp = levels.front()->loadFromFile();
	aliens.insert(aliens.end(), temp.begin(), temp.end());

	addSoundBuffer("blaster3");
}

Playing::~Playing()
{
	stopAllSounds();
	delete player;
	delete main_bg;
	delete layer1;
}

void Playing::update(float dt, sf::Event e)
{
	checkInput(dt, e);

	backgroundUpdates(dt);
	mapUpdates(dt);
	playerUpdates(dt);
	alienUpdates(dt);
	effectUpdates(dt);
	pickupUpdates(dt);

	tryStartingNewLevel();

	if (is_game_over)
		should_pop = true;

	if (should_pop)
		state_manager.popState();
}

void Playing::draw()
{
	main_bg->draw(window);
	layer1->draw(window);
	for (ParticleExplosion* pe : particle_explosions)
		pe->draw(window);
	for (Pickup* p : pickups)
		p->draw(window);
	player->draw(window);
	for (Explosion* e : sprite_explosions)
		e->draw(window);
	for (Projectile* p : player_projectiles)
		p->draw(window);
	for (Projectile* p : alien_projectiles)
		p->draw(window);
	for (Alien* a : aliens)
		a->draw(window);
}

void Playing::checkInput(float dt, sf::Event e)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		should_pop = true;
}

void Playing::mapUpdates(float dt)
{
	for (size_t i = 0; i < player_projectiles.size(); i++)
	{
		Projectile* proj = player_projectiles[i];
		proj->update(dt);
		if (proj->isOutOfMap())
		{
			delete player_projectiles[i];
			player_projectiles.erase(player_projectiles.begin() + i);
			i--;
		}
	}

	for (size_t i = 0; i < alien_projectiles.size(); i++)
	{
		Projectile* proj = alien_projectiles[i];
		proj->update(dt);
		if (proj->isOutOfMap())
		{
			delete alien_projectiles[i];
			alien_projectiles.erase(alien_projectiles.begin() + i);
			i--;
		}
	}
}

void Playing::playerUpdates(float dt)
{
	player->update(dt);
	if (player->isFiring())
	{
		std::vector<Projectile*> temp = player->getNewWeaponProjectiles();
		player_projectiles.insert(player_projectiles.end(), temp.begin(), temp.end());
	}

	for (size_t i = 0; i < alien_projectiles.size(); i++)
	{
		if (player->gotHitBy(alien_projectiles[i]))
		{
			if (player->shouldExplode())
			{
				playSound("blaster3", R::nextFloat(25, 40) / 100.f);
				particle_explosions.push_back(new ParticleExplosion(player->getPosition(), 3.f, 100));
				sprite_explosions.push_back(new Explosion(player->getPosition(), 1.5f, 7, 4.f));
			}

			delete alien_projectiles[i];
			alien_projectiles.erase(alien_projectiles.begin() + i);
			i--;

			if (player->lostAllLives())
				is_game_over = true;
		}
	}
}

void Playing::alienUpdates(float dt)
{
	for (size_t i = 0; i < aliens.size(); i++)
	{
		Alien* alien = aliens[i];

		for (size_t j = 0; j < player_projectiles.size(); j++)
		{
			if (alien->gotHitBy(player_projectiles[j]))
			{
				particle_explosions.push_back(new ParticleExplosion(alien->getPosition(), R::nextFloat(2, 4), 10));
				delete player_projectiles[j];
				player_projectiles.erase(player_projectiles.begin() + j);
				j--;
			}
		}

		alien->update(dt);

		if (alien->shouldDie())
		{
			playSound("blaster3", R::nextFloat(25, 40) / 100.f);
			particle_explosions.push_back(new ParticleExplosion(alien->getPosition(), R::nextFloat(2, 7), 100));
			sprite_explosions.push_back(new Explosion(alien->getPosition(), 1.f, R::nextInt(1, 7), 2.f));
			//pickups.push_back(new Money(alien->getPosition(), { 0, 150.f }, R::nextInt(0, 4)));

			delete aliens[i];
			aliens.erase(aliens.begin() + i);
			i--;
			continue;
		}

		if (alien->isFiring())
		{
			std::vector<Projectile*> temp = alien->getProjectiles();
			alien_projectiles.insert(alien_projectiles.end(), temp.begin(), temp.end());
		}
	}
}

void Playing::effectUpdates(float dt)
{
	for (size_t i = 0; i < particle_explosions.size(); i++)
	{
		particle_explosions[i]->update(dt);
		if (particle_explosions[i]->shouldDie())
		{
			delete particle_explosions[i];
			particle_explosions.erase(particle_explosions.begin() + i);
			i--;
		}
	}

	for (size_t i = 0; i < sprite_explosions.size(); i++)
	{
		sprite_explosions[i]->update(dt);
		if (sprite_explosions[i]->shouldDie())
		{
			delete sprite_explosions[i];
			sprite_explosions.erase(sprite_explosions.begin() + i);
			i--;
		}
	}
}

void Playing::backgroundUpdates(float dt)
{
	main_bg->update(dt);
	layer1->update(dt);
}

void Playing::pickupUpdates(float dt)
{
	for (size_t i = 0; i < pickups.size(); i++)
	{
		pickups[i]->update(dt);

		if (player->contains(pickups[i]))
			pickups[i]->giveBonus(player);

		if (pickups[i]->shouldDie() || pickups[i]->isOutOfMap())
		{
			delete pickups[i];
			pickups.erase(pickups.begin() + i);
			i--;
		}
	}
}

void Playing::tryStartingNewLevel()
{
	if (aliens.size() == 0)
	{
		active_level++;
		if (active_level > levels.size())
		{
			//should_pop = true;
		}
		else
		{
			std::vector<Alien*> temp = levels[active_level - 1]->loadFromFile();
			aliens.insert(aliens.end(), temp.begin(), temp.end());
		}
	}
}
