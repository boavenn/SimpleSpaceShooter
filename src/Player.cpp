#include "..\inc\Player.h"

Player::Player() : Phantom(20), stationary(sf::IntRect(0, 0, 70, 70), 3, 0.25f), movingleft(sf::IntRect(0, 70, 70, 70), 3, 0.25f),
					movingright(sf::IntRect(70, 70, -70, 70), 3, 0.25f), stationaryInvinc(sf::IntRect(210, 0, 70, 70), 3, 0.25f),
					movingleftInvinc(sf::IntRect(210, 70, 70, 70), 3, 0.25f), movingrightInvinc(sf::IntRect(280, 70, -70, 70), 3, 0.25f)
{
	velocity = { 0,0 };
	buffer.insert(std::make_pair("blaster2", ResourceManager::get().buffers.get("blaster2")));
	buffer.insert(std::make_pair("blaster3", ResourceManager::get().buffers.get("blaster3")));
	buffer.insert(std::make_pair("shield", ResourceManager::get().buffers.get("shield")));
	sprite.setTexture(ResourceManager::get().textures.get("player"));
	sprite.setOrigin({ 35.f,35.f });
	sprite.setPosition({ 683,731 });
	currHealth = 1.f;
}

void Player::input()
{
	float speed = 300.f * speedMod;
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
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
	checkInvincibilty(deltaTime);
	checkMovement(deltaTime);

	sprite.move(velocity * deltaTime);
}

bool Player::isHit(std::vector<Projectile>& projectiles)
{
	float half_width = sprite.getLocalBounds().width / 2.f;
	float half_height = sprite.getLocalBounds().height / 2.f;
	for (unsigned i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].getPosition().x >= sprite.getPosition().x - half_width && projectiles[i].getPosition().x <= sprite.getPosition().x + half_width &&
			projectiles[i].getPosition().y >= sprite.getPosition().y - half_height && projectiles[i].getPosition().y <= sprite.getPosition().y + half_height)
		{
			projectiles.erase(projectiles.begin() + i);

			if (!invincible)
			{
				if (lives > 0)
				{
					lives--;
					invincible = true;

					if(lives > 0)
						play("shield", 0.9f);

					if (curr_weapon_no > 1)
						curr_weapon_no--;
				}
			}
			return true;
		}
	}
	return false;
}

bool Player::gotPickup(std::vector<Pickup>& pickups)
{
	float half_width = sprite.getLocalBounds().width / 2.f;
	float half_height = sprite.getLocalBounds().height / 2.f;
	for (unsigned i = 0; i < pickups.size(); i++)
	{
		if (pickups[i].getPosition().x >= sprite.getPosition().x - half_width && pickups[i].getPosition().x <= sprite.getPosition().x + half_width &&
			pickups[i].getPosition().y >= sprite.getPosition().y - half_height && pickups[i].getPosition().y <= sprite.getPosition().y + half_height)
		{ 
			upgrade(pickups[i].getType());
			pickups.erase(pickups.begin() + i);
			return true;		
		}
	}
	return false;
}

void Player::upgrade(Pickup::PickupType type)
{
	switch (type)
	{
	case Pickup::PickupType::speedInc:
		if(speedMod < maxSpeedMod)
			speedMod += 0.05f;
		else
			score += 1000;
		break;
	case Pickup::PickupType::magazineSizeInc:
		if (magazineSize < maxMagazineSize)
			magazineSize += 1;
		else
			score += 1000;
		break;
	case Pickup::PickupType::bulletSpeedInc:
		if(bulletSpeedMod < maxBulletSpeedMod)
			bulletSpeedMod += 0.05f;
		else
			score += 1000;
		break;
	case Pickup::PickupType::reloadSpeedInc:
		if (reloadTime > minReloadTime)
			reloadTime -= 0.02f;
		else
			score += 1000;
		break;
	case Pickup::PickupType::dmgInc:
		dmgMod += 0.1f;
		break;
	case Pickup::PickupType::liveAdd:
		if(lives < maxLives)
			lives += 1;
		else
			score += 1000;
		break;
	case Pickup::PickupType::weaponUpgrade:
		if (curr_weapon_no < 5)
			curr_weapon_no++;
		else
			score += 1000;
		break;
	case Pickup::PickupType::weaponDowngrade:
		if (curr_weapon_no > 1)
			curr_weapon_no--;
		break;
	}
}

void Player::tryReload(float deltaTime)
{
	reloadTotalTime += deltaTime;
	if (reloadTotalTime >= reloadTime)
	{
		reloadTotalTime -= reloadTime;
		if (magazine_curr < magazineSize)
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
		{
			if (invincible)
				sprite.setTextureRect(movingrightInvinc.update(deltaTime));
			else 
				sprite.setTextureRect(movingright.update(deltaTime));
		}
		else
		{
			if (invincible)
				sprite.setTextureRect(movingleftInvinc.update(deltaTime));
			else 
				sprite.setTextureRect(movingleft.update(deltaTime));
		}
	}
	else
	{
		if (invincible)
			sprite.setTextureRect(stationaryInvinc.update(deltaTime));
		else
			sprite.setTextureRect(stationary.update(deltaTime));
	}

	if (sprite.getPosition().x <= 216)
		sprite.setPosition({ 216.0f, sprite.getPosition().y });
	if (sprite.getPosition().x >= 1150.f)
		sprite.setPosition({ 1150.f, sprite.getPosition().y });
}

void Player::checkInvincibilty(float deltaTime)
{
	if (invincible)
	{
		invincibilityTotalTime += deltaTime;
		if (invincibilityTotalTime >= invincibiltyTime)
		{
			invincibilityTotalTime = 0.f;
			invincible = false;
		}
	}
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
