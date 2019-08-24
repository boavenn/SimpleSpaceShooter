#pragma once
#include "Player.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Projectile.h"
#include "Explosion.h"
#include "Background.h"
#include "Random.h"

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
	void updateBackground(float deltaTime);
	void trySpawn(float deltaTime);

	Player player;
	Random rand;
	std::vector<Projectile> player_projectiles;
	std::vector<Projectile> enemy_projectiles;
	std::vector<Enemy*> enemies;
	std::vector<Explosion*> explosions;
	std::vector<Background> background_layers;
	float enemySpawnTime = 2.f;
	float enemyTotalTime = 0.f;
};


