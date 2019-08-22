#include "..\inc\Enemy.h"

Enemy::Enemy(float shootingDelay, float shootingChance, unsigned type)
	: Phantom(1), movement(sf::IntRect(0, type * 40, 40, 40), 2, 0.5f), gettingHit(sf::IntRect(80, type * 40, 40, 40), 1, 0.25f)
{
	velocity = { 0, 50 };
	buffer.push_back(ResourceManager::get().buffers.get("blaster1"));
	sprite.setTexture(ResourceManager::get().textures.get("enemies"));
	sprite.setOrigin({ 20.f,20.f });
	sprite.setPosition({ 683,-50 });
	this->shootingDelay = shootingDelay;
	this->shootingChance = shootingChance;
	this->type = type;
}

void Enemy::update(float deltaTime)
{
	try_shoot = false;

	tryFire(deltaTime);
	sprite.setTextureRect(movement.update(deltaTime));
	sprite.move(velocity * deltaTime);
}

void Enemy::tryFire(float deltaTime)
{
	shootingTotalTime += deltaTime;
	if (shootingTotalTime >= shootingDelay)
	{
		shootingTotalTime -= shootingDelay;

		unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
		std::default_random_engine eng(seed);
		float chance = float(eng() % 100);

		if (chance < shootingChance)
			try_shoot = true;
	}
}
