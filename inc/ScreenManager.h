#pragma once
#include "Player.h"
#include "ResourceManager.h"
#include "Projectile.h"
class ScreenManager
{
public:
	ScreenManager();
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
private:
	void checkFiredShots();
	void updateProjectiles(float deltaTime);

	Player player;
	std::vector<Projectile> player_projectiles;
};


