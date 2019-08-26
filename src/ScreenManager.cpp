#include "..\inc\ScreenManager.h"

ScreenManager::ScreenManager() : sound(30)
{
	background_layers.push_back(Background(0.06f, { 171.f,0 }, "background"));
	background_layers.push_back(Background(0.03f, { 171.f,0 }, "layer1"));
	background_layers.push_back(Background(0.03f, { 0,0 }, "sidebar"));
	background_layers.push_back(Background(0.03f, { 1195,0 }, "sidebar", 1));
	buffer.insert(std::make_pair("blaster3", ResourceManager::get().buffers.get("blaster3")));
	buffer.insert(std::make_pair("pickup", ResourceManager::get().buffers.get("pickup")));
}

void ScreenManager::update(float deltaTime)
{
	// order of these functions is important!
	// first we add, then update, otherwise some texture loading bugs may appear
	// (because of not updating sprites for the first time before drawing them)
	HUD.updateInfo(player);
	trySpawn(deltaTime);
	player.update(deltaTime);
	for (unsigned i = 0; i < enemies.size(); i++)
		enemies[i]->update(deltaTime);
	checkFiredShots();
	checkCollisions();
	updateProjectiles(deltaTime);
	updateExplosions(deltaTime);
	updateBackground(deltaTime);
	updateFloatingText(deltaTime);
}

void ScreenManager::updateProjectiles(float deltaTime)
{
	for (unsigned i = 0; i < player_projectiles.size(); i++)
	{
		player_projectiles[i].update(deltaTime);
		if (player_projectiles[i].isOut())
		{
			player_projectiles.erase(player_projectiles.begin() + i);
			i--;
		}
	}

	for (unsigned i = 0; i < enemy_projectiles.size(); i++)
	{
		enemy_projectiles[i].update(deltaTime);
		if (enemy_projectiles[i].isOut())
		{
			enemy_projectiles.erase(enemy_projectiles.begin() + i);
			i--;
		}
	}

	for (unsigned i = 0; i < pickups.size(); i++)
	{
		pickups[i].update(deltaTime);
		if (pickups[i].isOut())
		{
			pickups.erase(pickups.begin() + i);
			i--;
		}
	}
}

void ScreenManager::updateExplosions(float deltaTime)
{
	for (unsigned i = 0; i < explosions.size(); i++)
	{
		explosions[i]->update(deltaTime);
		if (explosions[i]->getCurrImg() == -1)
		{
			delete explosions[i];
			explosions.erase(explosions.begin() + i);
			i--;
		}
	}
}

void ScreenManager::updateBackground(float deltaTime)
{
	unsigned len = background_layers.size();
	for (unsigned i = 0; i < len; i++)
		background_layers[i].update(deltaTime);
}

void ScreenManager::updateFloatingText(float deltaTime)
{
	for (unsigned i = 0; i < floating_text.size(); i++)
	{
		floating_text[i]->update(deltaTime);
		if (floating_text[i]->dead())
		{
			delete floating_text[i];
			floating_text.erase(floating_text.begin() + i);
			i--;
		}
	}
}

void ScreenManager::trySpawn(float deltaTime)
{
	enemyTotalTime += deltaTime;
	if (enemyTotalTime >= enemySpawnTime)
	{
		enemyTotalTime -= enemySpawnTime;

		if (enemies.size() < 30)
		{
			float rand_x_pos = float(rand.getIntInRange(205, 1160));
			float typeChance = float(rand.getIntInRange(0, 100));

			unsigned type;
			if (typeChance < 40.f)
			{
				if (typeChance < 15.f)
					type = 2;
				else
					type = 1;
			}
			else
				type = 0;

			enemies.push_back(new Enemy(enemyHealthMod, 1.f, 10.f, type, { rand_x_pos, -50 }));
		}
	}
}

void ScreenManager::play(std::string name, float pitch, float vol)
{
	for (auto& x : sound)
	{
		if (x.getStatus() == 0)
		{
			x.setBuffer(buffer.at(name));
			x.setPitch(pitch);
			x.setVolume(vol);
			x.play();
			return;
		}
	}
}

void ScreenManager::checkFiredShots()
{
	if (player.isShooting())
	{
		Player::WeaponType type = player.shoot();
		float posx; // most left bullet position
		std::vector<sf::Vector2f> v; // consecutive bullets velocity
		switch (type)
		{
		case Player::WeaponType::oneshot:
			v = { {0,-300.f} };
			player_projectiles.push_back(Projectile(sf::IntRect(0, 0, 8, 16), v[0] * player.getBulletSpeedMod(), 5.f * player.getDmgMod()));
			player_projectiles.back().setInitialPosition({ player.getPosition().x, player.getPosition().y - 35.f });
			break;
		case Player::WeaponType::doubleshot:
			posx = -10.f;
			v = { {0,-300.f} };
			for (unsigned i = 0; i < 2; i++)
			{
				player_projectiles.push_back(Projectile(sf::IntRect(8, 0, 8, 16), v[0] * player.getBulletSpeedMod(), 5.f * player.getDmgMod()));
				player_projectiles.back().setInitialPosition({ player.getPosition().x + posx, player.getPosition().y - 35.f });
				posx += 20.f;
			}
			break;
		case Player::WeaponType::tripleshot:
			posx = -16.f;
			v = { {-80.f, -300.f}, {0.0f, -300.f}, {80.f, -300.f} };
			for (unsigned i = 0; i < 3; i++)
			{
				player_projectiles.push_back(Projectile(sf::IntRect(16, 0, 8, 16), v[i] * player.getBulletSpeedMod(), 10.f * player.getDmgMod()));
				player_projectiles.back().setInitialPosition({ player.getPosition().x + posx, player.getPosition().y - 35.f });
				posx += 16.f;
			}
			break;
		case Player::WeaponType::quadshot:
			posx = -24.f;
			v = { {-30.f, -300.f}, {-10.0f, -300.f}, {10.f, -300.f}, {30.f, -300.f} };
			for (unsigned i = 0; i < 4; i++)
			{
				player_projectiles.push_back(Projectile(sf::IntRect(24, 0, 8, 16), v[i] * player.getBulletSpeedMod(), 10.f * player.getDmgMod()));
				player_projectiles.back().setInitialPosition({ player.getPosition().x + posx, player.getPosition().y - 35.f });
				posx += 16.f;
			}
			break;
		case Player::WeaponType::plasma:
			v = { { -40, -450.f }, {40, -450} };
			for (unsigned i = 0; i < 2; i++)
			{
				player_projectiles.push_back(Projectile(sf::IntRect(0, 16, 12, 18), v[i] * player.getBulletSpeedMod(), 15.f * player.getDmgMod()));
				player_projectiles.back().setInitialPosition({ player.getPosition().x, player.getPosition().y - 35.f });
			}
			break;
		}
	}

	for (unsigned i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->isShooting())
		{
			sf::Vector2f v;
			float vMod = float(rand.getIntInRange(100, 200)) / 100.f;
			switch (enemies[i]->getType())
			{
			case 0:
				v = { 0, 250 };
				enemy_projectiles.push_back(Projectile(sf::IntRect(33, 0, 6, 16), v * vMod, 1000.f ));
				enemy_projectiles.back().setInitialPosition({ enemies[i]->getPosition().x, enemies[i]->getPosition().y + 20.f });
				break;
			case 1:
				v = { 0, 250 };
				enemy_projectiles.push_back(Projectile(sf::IntRect(39, 0, 6, 16), v * vMod, 1000.f));
				enemy_projectiles.back().setInitialPosition({ enemies[i]->getPosition().x, enemies[i]->getPosition().y + 20.f });
				break;
			case 2:
				v.y = 250;
				v.x = v.y * (player.getPosition().x + float(rand.getIntInRange(-100, 100)) - enemies[i]->getPosition().x) / (player.getPosition().y - enemies[i]->getPosition().y);
				enemy_projectiles.push_back(Projectile(sf::IntRect(12, 17, 12, 12), v * vMod, 1000.f));
				enemy_projectiles.back().setInitialPosition({ enemies[i]->getPosition().x, enemies[i]->getPosition().y + 20.f });
				break;
			}
		}
	}
}

void ScreenManager::checkCollisions()
{
	if (player.isHit(enemy_projectiles))
	{
		if (player.getLives() == 0)
			game_over = true;
	}

	if (player.gotPickup(pickups))
	{
		play("pickup", 1.5f);
	}

	for (unsigned i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->isHit(player_projectiles))
		{
			floating_text.push_back(new FloatingText("- " + std::to_string(int(enemies[i]->getLastHitDmg())),
			{ enemies[i]->getPosition().x + float(rand.getIntInRange(-20,20)), enemies[i]->getPosition().y + float(rand.getIntInRange(-20,20)) }, sf::Color::Red));

			if (enemies[i]->died)
			{
				play("blaster3", 0.3f); // actually blaster3 sound with modified pitch makes better explosion sound than actual explosion lol
				explosions.push_back(new Explosion(enemies[i]->getPosition()));

				float pickupSpawningChance = float(rand.getIntInRange(0, 100));
				if (pickupSpawningChance < 20.f)
					pickups.push_back(Pickup(enemies[i]->getPosition()));

				player.addScore(unsigned(enemies[i]->getScoreForKill() * scoreMod));
				player.addKill();

				if (player.getKills() % 30 == 0)
				{
					if (enemySpawnTime > 0.5f)
					{
						enemySpawnTime -= 0.2f;
						background_layers[0].changeSwitchTime(0.005f);

						for (unsigned i = 1; i < background_layers.size(); i++)
							background_layers[i].changeSwitchTime(0.0025f);
					}

					enemyHealthMod += 0.2f;
					scoreMod += 0.2f;
				}

				floating_text.push_back(new FloatingText("+ " + std::to_string(int(enemies[i]->getScoreForKill() * scoreMod)),
				{ enemies[i]->getPosition().x + float(rand.getIntInRange(-20,20)), enemies[i]->getPosition().y - 30.f }, sf::Color::White));

				delete enemies[i]; // firstly we delete an object a pointer is pointing to
				enemies.erase(enemies.begin() + i); // and then that pointer
				i--;
			}
		}
	}
}

void ScreenManager::draw(sf::RenderWindow& w)
{
	for (unsigned i = 0; i < 2; i++)
		background_layers[i].draw(w);

	unsigned len = player_projectiles.size();
	for (unsigned i = 0; i < len; i++)
		player_projectiles[i].draw(w);

	len = pickups.size();
	for (unsigned i = 0; i < len; i++)
		pickups[i].draw(w);

	len = enemy_projectiles.size();
	for (unsigned i = 0; i < len; i++)
		enemy_projectiles[i].draw(w);

	len = enemies.size();
	for (unsigned i = 0; i < len; i++)
		enemies[i]->draw(w);

	len = explosions.size();
	for (unsigned i = 0; i < len; i++)
		explosions[i]->draw(w);

	for (unsigned i = 2; i < 4; i++)  // we draw sidebars as last so enemies can go behind it
		background_layers[i].draw(w);

	len = floating_text.size();
	for (unsigned i = 0; i < len; i++)
		floating_text[i]->draw(w);

	HUD.draw(w);
	player.draw(w);
}
