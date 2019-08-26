#include "..\inc\Enemy.h"

Enemy::Enemy(float healthMod, float shootingDelay, float shootingChance, unsigned type, sf::Vector2f pos)
	: Phantom(1), movement(setMovRect(type), 2, 0.5f), gettingHit(setHitRect(type), 1, 0.1f, 0)
{
	velocity = { 0, 50 };
	buffer.insert(std::make_pair("blaster1", ResourceManager::get().buffers.get("blaster1")));
	buffer.insert(std::make_pair("blaster4", ResourceManager::get().buffers.get("blaster4")));
	sprite.setTexture(ResourceManager::get().textures.get("enemies"));
	sprite.setOrigin({ setMovRect(type).width / 2.f, setMovRect(type).height / 2.f });
	sprite.setPosition(pos);
	this->shootingDelay = shootingDelay;
	this->shootingChance = shootingChance;
	this->type = type;
	maxDepth = float(rand.getIntInRange(150, 250));

	switch (type)
	{
	case 0:
		scoreForKill = 50;
		currHealth = 10.f * healthMod;
		break;
	case 1:
		scoreForKill = 75;
		currHealth = 15.f * healthMod;
		break;
	case 2:
		scoreForKill = 100;
		currHealth = 25.f * healthMod;
		break;
	}
}

void Enemy::update(float deltaTime)
{
	try_shoot = false;

	updateMovement(deltaTime);
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

void Enemy::updateMovement(float deltaTime)
{
	if (getPosition().x < 300.f)
		turning_right = true;
	else if (getPosition().x > 1066.f)
		turning_right = false;

	if (getPosition().y > maxDepth)
		try_go_up = true;
	else if (getPosition().y < 100.f)
		try_go_up = false;

	movementTotalTime += deltaTime;
	turningTotalTime += deltaTime;

	if (movementTotalTime >= movementTick)
	{
		movementTotalTime -= movementTick;

		if (turningTotalTime >= turningTick)
		{
			turningTotalTime -= turningTick;

			turning_right = bool(rand.getIntInRange(0, 2));
			try_go_up = bool(rand.getIntInRange(0, 2));
		}

		if (turning_right)
		{
			if (velocity.x < -40.f)
				velocity.x += 30.f;
			else
				velocity.x += 10.f;
		}
		else
		{
			if (velocity.x > 40.f)
				velocity.x -= 30.f;
			else
				velocity.x -= 10.f;
		}

		if (try_go_up)
		{
			if (velocity.y > 40.f)
				velocity.y -= 30.f;
			else
				velocity.y -= 10.f;
		}
		else
		{
			if (velocity.y < -40.f)
				velocity.y += 30.f;
			else
				velocity.y += 10.f;
		}
	}
}

sf::IntRect Enemy::setMovRect(unsigned type)
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

sf::IntRect Enemy::setHitRect(unsigned type)
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
