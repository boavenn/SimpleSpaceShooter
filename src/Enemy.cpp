#include "..\inc\Enemy.h"

Enemy::Enemy(float healthMod, float shootingDelay, float shootingChance, unsigned type, sf::Vector2f pos)
	: Phantom(1), movement(sf::IntRect(0, type * 40, 40, 40), 2, 0.5f), gettingHit(sf::IntRect(80, type * 40, 40, 40), 1, 0.1f, 0)
{
	velocity = { 0, 50 };
	buffer.push_back(ResourceManager::get().buffers.get("blaster1"));
	sprite.setTexture(ResourceManager::get().textures.get("enemies"));
	sprite.setOrigin({ 20.f,20.f });
	sprite.setPosition(pos);
	this->shootingDelay = shootingDelay;
	this->shootingChance = shootingChance;
	this->type = type;

	switch (type)
	{
	case 0:
		currHealth = 15.f * healthMod;
		break;
	case 1:
		currHealth = 20.f * healthMod;
		break;
	}
}

void Enemy::update(float deltaTime)
{
	try_shoot = false;

	tryFire(deltaTime);
	if (gotHit)
	{
		sprite.setTextureRect(gettingHit.update(deltaTime));
		if (gettingHit.getCurrImg() == -1)
			gotHit = false;
	}
	else
		sprite.setTextureRect(movement.update(deltaTime));
	sprite.move(velocity * deltaTime);
}

void Enemy::tryFire(float deltaTime)
{
	shootingTotalTime += deltaTime;
	if (shootingTotalTime >= shootingDelay)
	{
		shootingTotalTime -= shootingDelay;

		unsigned seed = static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count());
		std::default_random_engine eng(seed);
		float chance = float(eng() % 100);

		if (chance < shootingChance)
			try_shoot = true;
	}
}
