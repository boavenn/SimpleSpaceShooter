#include "..\inc\Player.h"

Player::Player() : Phantom(20), stationary(sf::IntRect(0, 0, 70, 70), 3, 0.25f), movingleft(sf::IntRect(0, 70, 70, 70), 3, 0.25f),
				   movingright(sf::IntRect(70, 70, -70, 70), 3, 0.25f)
{
	velocity = { 0,0 };
	buffer.insert(std::make_pair("blaster2", ResourceManager::get().buffers.get("blaster2")));
	buffer.insert(std::make_pair("blaster3", ResourceManager::get().buffers.get("blaster3")));
	sprite.setTexture(ResourceManager::get().textures.get("player"));
	sprite.setOrigin({ 35.f,35.f });
	sprite.setPosition({ 683,731 });
	currHealth = 1.f;
}

void Player::input()
{
	float speed = 300.f;
	velocity.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= speed;
		moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += speed;
		moving = true;
		facing_right = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
			if (magazine_curr > 0)
			{
				if (shootTotalTime >= shotGap)
				{
					shootTotalTime -= shotGap;
					magazine_curr--;
					try_shoot = true;
					playShotSound();
				}			
			}
	}
}

void Player::update(float deltaTime)
{
	curr_weapon = static_cast<WeaponType>(curr_weapon_no);
	moving = false;
	facing_right = false;
	try_shoot = false;

	tryReload(deltaTime);
	tryFire(deltaTime);
	input();
	checkMovement(deltaTime);

	sprite.move(velocity * deltaTime);
}

void Player::tryReload(float deltaTime)
{
	reloadTotalTime += deltaTime;
	if (reloadTotalTime >= reloadTime)
	{
		reloadTotalTime -= reloadTime;
		if (magazine_curr < magazine_size)
			magazine_curr++;
	}
}

void Player::tryFire(float deltaTime)
{
	shootTotalTime += deltaTime;
	if (shootTotalTime >= shotGap)
		shootTotalTime = shotGap;
}

void Player::checkMovement(float deltaTime)
{
	if (moving)
	{
		if (facing_right)
			sprite.setTextureRect(movingright.update(deltaTime));
		else
			sprite.setTextureRect(movingleft.update(deltaTime));
	}
	else
		sprite.setTextureRect(stationary.update(deltaTime));

	if (sprite.getPosition().x <= 216)
		sprite.setPosition({ 216.0f, sprite.getPosition().y });
	if (sprite.getPosition().x >= 1150.f)
		sprite.setPosition({ 1150.f, sprite.getPosition().y });
}

void Player::playShotSound()
{
	switch (curr_weapon)
	{
	case oneshot:
		play("blaster2", 1.f);
		break;
	case doubleshot:
		play("blaster2", 0.8f);
		break;
	case tripleshot:
		play("blaster3", 1.f);
		break;
	case quadshot:
		play("blaster3", 0.8f);
		break;
	case plasma:
		play("blaster3", 0.5f);
		break;
	}
}
