#include "..\inc\Enemy.h"

Enemy::Enemy(float healthMod, float shootingDelay, float shootingChance, unsigned type, sf::Vector2f pos)
	: Phantom(1), movement(getMovRect(type), 2, 0.5f), gettingHit(getHitRect(type), 1, 0.1f, 0)
{
	velocity = { 0, 50 };
	buffer.insert(std::make_pair("blaster1", ResourceManager::get().buffers.get("blaster1")));
	buffer.insert(std::make_pair("blaster4", ResourceManager::get().buffers.get("blaster4")));
	sprite.setTexture(ResourceManager::get().textures.get("enemies"));
	sprite.setOrigin({ getMovRect(type).width / 2.f, getMovRect(type).height / 2.f });
	sprite.setPosition(pos);
	this->shootingDelay = shootingDelay;
	this->shootingChance = shootingChance;
	this->type = type;

	switch (type)
	{
	case 0:
		currHealth = 10.f * healthMod;
		break;
	case 1:
		currHealth = 15.f * healthMod;
		break;
	case 2:
		currHealth = 25.f * healthMod;
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

		float chance = float(rand.getIntInRange(0, 100));

		if (chance < shootingChance)
		{
			playShotSound();
			try_shoot = true;
		}
	}
}

void Enemy::playShotSound()
{
	switch (type)
	{
	case 0:
		play("blaster1", 1.f);
		break;
	case 1:
		play("blaster1", 1.f);
		break;
	case 2:
		play("blaster4", 1.f);
		break;
	}
}

sf::IntRect Enemy::getMovRect(unsigned type)
{
	switch (type)
	{
	case 0:
		return sf::IntRect(0, 0, 40, 40);
		break;
	case 1:
		return sf::IntRect(0, 40, 40, 40);
		break;
	case 2:
		return sf::IntRect(0, 80, 50, 50);
		break;
	default:
		return sf::IntRect(0, 0, 40, 40);
		break;
	}
}

sf::IntRect Enemy::getHitRect(unsigned type)
{
	switch (type)
	{
	case 0:
		return sf::IntRect(80, 0, 40, 40);
		break;
	case 1:
		return sf::IntRect(80, 40, 40, 40);
		break;
	case 2:
		return sf::IntRect(100, 80, 50, 50);
		break;
	default:
		return sf::IntRect(80, 0, 40, 40);
		break;
	}
}
