#include "..\inc\Enemy.h"

Enemy::Enemy(float shootingTime, float shootChance, unsigned type)
	: Phantom(1), movement(sf::IntRect(0, type * 40, 40, 40), 2, 0.5f), gettingHit(sf::IntRect(80, type * 40, 40, 40), 1, 0.25f)
{
	velocity = { 0, 50 };
	buffer.push_back(ResourceManager::get().buffers.get("blaster1"));
	sprite.setTexture(ResourceManager::get().textures.get("enemies"));
	sprite.setOrigin({ 20.f,20.f });
	sprite.setPosition({ 683,-50 });
}

void Enemy::update(float deltaTime)
{
	try_shoot = false;

	sprite.setTextureRect(movement.update(deltaTime));

	sprite.move(velocity * deltaTime);
}
