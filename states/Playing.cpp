#include "Playing.hpp"
#include <iostream>

bool Playing::should_pause_sounds = false;

Playing::Playing(sf::RenderWindow& w, StateManager& sm) : State(w, sm), SoundMaking(20)
{
	main_bg = new Background(0.06f, { 171.f, 0 }, "background");
	layer1 = new Background(0.04f, { 171.f, 0 }, "layer1");
	sidebar_l.setTexture(ResourceManager::get().textures.get("sidebar"));
	sidebar_l.setPosition({ 0, 0 });
	sidebar_r.setTexture(ResourceManager::get().textures.get("sidebar"));
	sidebar_r.setTextureRect({ 171, 0, -171, 768 });
	sidebar_r.setPosition({ float(WindowProperties::getWidth() - 171), 0 });
	hud = new HUD(player);
	level_teller = new Box({ 100.f, 50.f }, { float(WindowProperties::getWidth() / 2.f), -50.f });
	level_teller->setFont("MonospaceTypewriter");
	level_teller->setText("Level 1");
	level_teller->setTextIdleColor(sf::Color::Green);
	level_teller->setTextScale({ 0.5f, 0.5f });
	level_teller->centerText();

	shop_teller = new Box({ 100.f, 50.f }, { 50.f, float(WindowProperties::getHeight()) / 2.f });
	shop_teller->setFont("MonospaceTypewriter");
	shop_teller->setText("Shopping time");
	shop_teller->setTextIdleColor(sf::Color::Green);
	shop_teller->setTextScale({ 0.5f, 0.5f });
	shop_teller->centerText();

	for (int i = 1; i <= 5; i++)
		levels.push_back(new Level(i));

	std::vector<Alien*> temp = levels.front()->loadFromFile();
	aliens.insert(aliens.end(), temp.begin(), temp.end());

	addSoundBuffer("blaster3");
	addSoundBuffer("battle");

	playSound("battle", 1.f, 50.f, true);
}

Playing::~Playing()
{
	delete player;
	delete main_bg;
	delete layer1;
	delete hud;
	delete level_teller;
	delete shop_teller;
	for (size_t i = 0; i < player_projectiles.size();)
	{
		delete player_projectiles[0];
		player_projectiles.erase(player_projectiles.begin());
	}
	for (size_t i = 0; i < levels.size();)
	{
		delete levels[0];
		levels.erase(levels.begin());
	}
	for (size_t i = 0; i < aliens.size();)
	{
		delete aliens[0];
		aliens.erase(aliens.begin());
	}
	for (size_t i = 0; i < alien_projectiles.size();)
	{
		delete alien_projectiles[0];
		alien_projectiles.erase(alien_projectiles.begin());
	}
	for (size_t i = 0; i < pickups.size();)
	{
		delete pickups[0];
		pickups.erase(pickups.begin());
	}
	for (size_t i = 0; i < floating_texts.size();)
	{
		delete floating_texts[0];
		floating_texts.erase(floating_texts.begin());
	}
	for (size_t i = 0; i < particle_explosions.size();)
	{
		delete particle_explosions[0];
		particle_explosions.erase(particle_explosions.begin());
	}
	for (size_t i = 0; i < sprite_explosions.size();)
	{
		delete sprite_explosions[0];
		sprite_explosions.erase(sprite_explosions.begin());
	}
}

void Playing::update(float dt, sf::Event e)
{
	if (state_manager.isOnTop(this) && shop_active)
	{
		shop_active = false;
		playSound("battle", 1.f, 50.f, true);
	}

	checkInput(dt, e);

	backgroundUpdates(dt);
	mapUpdates(dt);
	if(!gameover_loop)
		playerUpdates(dt);
	alienUpdates(dt);
	floatingTextUpdates(dt);
	effectUpdates(dt);
	pickupUpdates(dt);
	hud->update(dt);

	if (should_add_shop)
	{
		if (pickups.size() == 0 && !should_tell_shop)
		{
			state_manager.pushState(std::make_unique<Shop>(window, state_manager, player, active_level), 0, 0);
			shop_active = true;
			should_add_shop = false;
			resetTransitionFreeze();
			stopAllSounds();
		}
	}
	else
	{
		tryStartingNewLevel();
	}

	if (should_tell_level)
		levelTellerUpdate(dt);

	if (should_tell_shop)
		shopTellerUpdate(dt);

	if (is_game_over)
	{
		stopAllSounds();
		state_manager.pushState(std::make_unique<GameOver>(window, state_manager, player->getScore()));
		is_game_over = false;
		gameover_loop = true;
	}

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
	if(!gameover_loop)
		player->draw(window);
	for (Explosion* e : sprite_explosions)
		e->draw(window);
	for (Projectile* p : player_projectiles)
		p->draw(window);
	for (Projectile* p : alien_projectiles)
		p->draw(window);
	for (Alien* a : aliens)
		a->draw(window);
	for (FloatingText* f : floating_texts)
		f->draw(window);
	shop_teller->draw(window);
	window.draw(sidebar_l);
	window.draw(sidebar_r);
	hud->draw(window);
	level_teller->draw(window);
}

void Playing::checkInput(float dt, sf::Event e)
{
	if (isAbleToInput(dt))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !gameover_loop)
		{
			stopAllSounds();
			should_pop = true;
		}
	}
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
			tryAddingPickup(alien->getPosition());
			player->addScore(alien->getScore());
			floating_texts.push_back(new FloatingText(std::to_string(alien->getScore()), { alien->getPosition().x + R::nextFloat(-30, 30),  alien->getPosition().y + R::nextFloat(-30, 30) }));

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

void Playing::floatingTextUpdates(float dt)
{
	for (size_t i = 0; i < floating_texts.size(); i++)
	{
		floating_texts[i]->update(dt);
		if (floating_texts[i]->isDead())
		{
			delete floating_texts[i];
			floating_texts.erase(floating_texts.begin() + i);
			i--;
		}
	}
}

void Playing::levelTellerUpdate(float dt)
{
	sf::Vector2f v = { 0, 250.f };
	level_teller->move(v * dt);
	if (level_teller->getPosition().y > float(WindowProperties::getHeight()))
	{
		should_tell_level = false;
		level_teller->setPosition({ float(WindowProperties::getWidth() / 2.f), -50.f });
	}
}

void Playing::shopTellerUpdate(float dt)
{
	sf::Vector2f v = { 300, 0.f };
	shop_teller->move(v * dt);
	if (shop_teller->getPosition().x > float(WindowProperties::getWidth()) - 50.f)
	{
		should_tell_shop = false;
		shop_teller->setPosition({ 50.f, float(WindowProperties::getHeight()) / 2.f });
	}
}

void Playing::tryAddingPickup(sf::Vector2f pos)
{
	int chance = 25;
	sf::Vector2f speed = { 0, R::nextFloat(200, 300) };

	if (R::nextInt(0, 101) < chance)
	{
		int special = 5;
		int money = 40;
		int stats = 100;

		int r1 = R::nextInt(0, 101);
		if (r1 < special)
			pickups.push_back(new Health(pos, speed));
		else if (r1 < money)
		{
			int white = 40;
			int yellow = 70;
			int green = 90;
			int blue = 100;

			int r2 = R::nextInt(0, 101);
			if (r2 < white)
				pickups.push_back(new Money(pos, speed, 0));
			else if (r2 < yellow)
				pickups.push_back(new Money(pos, speed, 1));
			else if (r2 < green)
				pickups.push_back(new Money(pos, speed, 2));
			else
				pickups.push_back(new Money(pos, speed, 3));
		}
		else if (r1 <= stats)
		{
			int proj_speed = 5;
			int bullet = 15;
			int firerate = 35;
			int reload = 70;
			int sp = 100;

			int r2 = R::nextInt(0, 101);
			if (r2 < proj_speed)
				pickups.push_back(new BulletSpeed(pos, speed));
			else if (r2 < bullet)
				pickups.push_back(new BulletCapacity(pos, speed));
			else if (r2 <= firerate)
				pickups.push_back(new FireRate(pos, speed));
			else if (r2 <= reload)
				pickups.push_back(new ReloadTime(pos, speed));
			else
				pickups.push_back(new Speed(pos, speed));
		}
			
	}
}

void Playing::tryStartingNewLevel()
{
	if (aliens.size() == 0 && active_level < levels.size())
	{
		if (active_level % 2 == 0 && !shop_added)
		{
			should_add_shop = true;
			should_tell_shop = true;
			shop_added = true;
		}
		else
		{
			active_level++;
			should_tell_level = true;
			shop_added = false;
			level_teller->setText("Level " + std::to_string(active_level));
			level_teller->centerText();

			std::vector<Alien*> temp = levels[active_level - 1]->loadFromFile();
			aliens.insert(aliens.end(), temp.begin(), temp.end());
			hud->setLevel(active_level);
		}
	}
}
