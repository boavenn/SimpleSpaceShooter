#include "Playing.hpp"

bool Playing::should_pause_sounds = false;

Playing::Playing(sf::RenderWindow& w, StateManager& sm) : State(w, sm), SoundMaking(20)
{
	main_bg = new Background(0.06f, { 171.f, 0 }, "background");
	layer1 = new Background(0.04f, { 171.f, 0 }, "layer1");

	for (int i = 0; i < 5; i++)
	{
		aliens.push_back(new Alien01(20.f, { 500.f, 200.f + 50 * i }));
		aliens.push_back(new Alien01(20.f, { 570.f, 200.f + 50 * i }));
		aliens.push_back(new Alien01(20.f, { 640.f, 200.f + 50 * i }));
		aliens.push_back(new Alien01(20.f, { 710.f, 200.f + 50 * i }));
		aliens.push_back(new Alien01(20.f, { 780.f, 200.f + 50 * i }));
		aliens.push_back(new Alien01(20.f, { 850.f, 200.f + 50 * i }));
	}

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

	main_bg->update(dt);
	layer1->update(dt);
	playerUpdates(dt);
	alienUpdates(dt);
	effectUpdates(dt);

	if (should_pop)
		state_manager.popState();
}

void Playing::draw()
{
	main_bg->draw(window);
	layer1->draw(window);
	for (ParticleExplosion* pe : particle_explosions)
		pe->draw(window);
	for (Explosion* e : sprite_explosions)
		e->draw(window);
	player->draw(window);
	for (Projectile* p : player_projectiles)
		p->draw(window);
	for (Alien* a : aliens)
		a->draw(window);
}

void Playing::checkInput(float dt, sf::Event e)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		should_pop = true;
}

void Playing::playerUpdates(float dt)
{
	player->update(dt);
	if (player->isFiring())
	{
		std::vector<Projectile*> temp = player->getNewWeaponProjectiles();
		player_projectiles.insert(player_projectiles.end(), temp.begin(), temp.end());
	}

	for (size_t i = 0; i < player_projectiles.size(); i++)
	{
		Projectile* proj = player_projectiles[i];
		proj->update(dt);
		if (proj->isOutOfMap())
			player_projectiles.erase(player_projectiles.begin() + i);
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
				player_projectiles.erase(player_projectiles.begin() + j);
				particle_explosions.push_back(new ParticleExplosion(alien->getPosition(), 10, R::nextFloat(2, 4)));
			}
		}
		alien->update(dt);
		if (alien->shouldDie())
		{
			playSound("blaster3", R::nextFloat(25, 40) / 100.f);
			particle_explosions.push_back(new ParticleExplosion(alien->getPosition(), R::nextFloat(2, 7), 100));
			sprite_explosions.push_back(new Explosion(alien->getPosition(), 1.f, R::nextInt(1, 5)));
			aliens.erase(aliens.begin() + i);
			i--;		
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
