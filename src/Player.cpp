#include "..\inc\Player.h"

Player::Player() : stationary(sf::IntRect(0, 0, 70, 70), 3, 0.25f), movingleft(sf::IntRect(0, 70, 70, 70), 3, 0.25f), 
				   movingright(sf::IntRect(70, 70, -70, 70), 3, 0.25f), sound(20)
{
	velocity = { 0,0 };
	buffer.push_back(ResourceManager::get().buffers.get("blaster1"));
	sprite.setTexture(ResourceManager::get().textures.get("player"));
	sprite.setOrigin({ 35.f,35.f });
	sprite.setPosition({ 683,731 });
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
					play(0, 1.f, 100.f);
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

	reloadTotalTime += deltaTime;
	if (reloadTotalTime >= reloadTime)
	{
		reloadTotalTime -= reloadTime;
		if (magazine_curr < magazine_size)
			magazine_curr++;
	}

	shootTotalTime += deltaTime;
	if (shootTotalTime >= shotGap)
		shootTotalTime = shotGap;

	input();

	if (moving)
	{
		if (facing_right)
			sprite.setTextureRect(movingright.update(deltaTime));
		else
			sprite.setTextureRect(movingleft.update(deltaTime));
	}
	else
		sprite.setTextureRect(stationary.update(deltaTime));

	sprite.move(velocity * deltaTime);
}

void Player::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}

void Player::play(int buffer_no, float pitch, float vol)
{
	for (auto& x : sound)
	{
		if (x.getStatus() == 0)
		{
			x.setBuffer(buffer[buffer_no]);
			x.setPitch(pitch);
			x.setVolume(vol);
			x.play();
			return;
		}
	}
}
