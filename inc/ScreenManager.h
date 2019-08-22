#pragma once
#include "Player.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Projectile.h"
#include "Explosion.h"
#include <random>
#include <chrono>

class ScreenManager
{
public:
	ScreenManager();
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);

private:
	void checkFiredShots();
	void checkCollisions();
	void updateProjectiles(float deltaTime);
	void updateExplosions(float deltaTime);
	void trySpawn(float deltaTime);

	Player player;
	std::vector<Projectile> player_projectiles;
	std::vector<Projectile> enemy_projectiles;
	std::vector<Enemy*> enemies;
	std::vector<Explosion*> explosions;
	float enemySpawnTime = 2.f;
	float enemyTotalTime = 0.f;
};


