#include "..\inc\ScreenManager.h"

ScreenManager::ScreenManager()
{

}

void ScreenManager::update(float deltaTime)
{
	player.update(deltaTime);
	checkFiredShots();
	updateProjectiles(deltaTime);
}

void ScreenManager::updateProjectiles(float deltaTime)
{
	for (unsigned i = 0; i < player_projectiles.size(); i++)
	{
		player_projectiles[i].update(deltaTime);
		if (player_projectiles[i].isOut())
		{
			player_projectiles.erase(player_projectiles.begin() + i);
		}
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
}

void ScreenManager::draw(sf::RenderWindow& w)
{
	unsigned len = player_projectiles.size();
	for (unsigned i = 0; i < len; i++)
		player_projectiles[i].draw(w);
	player.draw(w);
}
