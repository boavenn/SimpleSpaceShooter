#include "..\inc\ScreenManager.h"

ScreenManager::ScreenManager()
{

}

void ScreenManager::update(float deltaTime)
{
	player.update(deltaTime);
	for (unsigned i = 0; i < enemies.size(); i++)
		enemies[i].update(deltaTime);
	checkFiredShots();
	updateProjectiles(deltaTime);
	trySpawn(deltaTime);
}

void ScreenManager::updateProjectiles(float deltaTime)
{
	for (unsigned i = 0; i < player_projectiles.size(); i++)
	{
		player_projectiles[i].update(deltaTime);
		if (player_projectiles[i].isOut())
			player_projectiles.erase(player_projectiles.begin() + i);
	}

	for (unsigned i = 0; i < enemy_projectiles.size(); i++)
	{
		enemy_projectiles[i].update(deltaTime);
		if (enemy_projectiles[i].isOut())
			enemy_projectiles.erase(enemy_projectiles.begin() + i);
	}
}

void ScreenManager::trySpawn(float deltaTime)
{
	enemyTotalTime += deltaTime;
	if (enemyTotalTime >= enemySpawnTime)
	{
		enemyTotalTime -= enemySpawnTime;
		enemies.push_back(Enemy(2.f, 20.f, 0));
	}
}

void ScreenManager::checkFiredShots()
{
	if (player.isShooting())
	{
		Player::WeaponType type = player.shoot();
		switch (type)
		{
		case Player::WeaponType::oneshot:
			player_projectiles.push_back(Projectile(sf::IntRect(0, 0, 8, 16), { 0,-250.f }, 5.f));
			player_projectiles.back().setInitialPosition({ player.getPosition().x, player.getPosition().y - 35.f });
			break;
		}
	}

	for (unsigned i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isShooting())
		{
			switch (enemies[i].getType())
			{
			case 0:
				enemy_projectiles.push_back(Projectile(sf::IntRect(33, 0, 6, 16), { 0, 250.f }, 1000.f ));
				enemy_projectiles.back().setInitialPosition({ enemies[i].getPosition().x, enemies[i].getPosition().y + 20.f });
				break;
			case 1:
				enemy_projectiles.push_back(Projectile(sf::IntRect(39, 0, 6, 16), { 0, 250.f }, 1000.f));
				enemy_projectiles.back().setInitialPosition({ enemies[i].getPosition().x, enemies[i].getPosition().y + 20.f });
				break;
			}
		}
	}
}

void ScreenManager::draw(sf::RenderWindow& w)
{
	unsigned len = player_projectiles.size();
	for (unsigned i = 0; i < len; i++)
		player_projectiles[i].draw(w);

	len = enemy_projectiles.size();
	for (unsigned i = 0; i < len; i++)
		enemy_projectiles[i].draw(w);

	len = enemies.size();
	for (unsigned i = 0; i < len; i++)
		enemies[i].draw(w);

	player.draw(w);
}
