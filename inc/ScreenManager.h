#pragma once
#include "Player.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Projectile.h"
#include "Explosion.h"
#include "Background.h"
#include "Random.h"
#include "Pickup.h"
#include <unordered_map>

class ScreenManager
{
public:
	ScreenManager();
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);

	bool game_over = false; // TODO: add Game Over screen

private:
	void checkFiredShots();
	void checkCollisions();
	void updateProjectiles(float deltaTime);
	void updateExplosions(float deltaTime);
	void updateBackground(float deltaTime);
	void trySpawn(float deltaTime);
	void play(std::string name, float pitch, float vol = 100.f);

	Player player;
	Random rand;
	std::vector<Projectile> player_projectiles;
	std::vector<Projectile> enemy_projectiles;
	std::vector<Enemy*> enemies;
	std::vector<Pickup> pickups;
	std::vector<Explosion*> explosions;
	std::vector<Background> background_layers;
	std::unordered_map<std::string, sf::SoundBuffer> buffer;
	std::vector<sf::Sound> sound;
	float enemySpawnTime = 2.f;
	float enemyTotalTime = 0.f;
};


