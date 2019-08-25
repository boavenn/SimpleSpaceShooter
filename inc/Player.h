#pragma once
#include "Phantom.h"
#include "Pickup.h"

class Player : public Phantom
{
public:
	enum WeaponType
	{
		oneshot = 1,
		doubleshot,
		tripleshot,
		quadshot,
		plasma
	};

public:
	Player();
	void input();
	void update(float deltaTime);
	bool gotPickup(std::vector<Pickup>& pickups);
	void upgrade(Pickup::PickupType type);
	const WeaponType& shoot() { return curr_weapon; }
	float getBulletSpeedMod() { return bulletSpeedMod; };
	bool isGameOver() { return game_over; };

private:
	void tryReload(float deltaTime);
	void tryFire(float deltaTime);
	void checkMovement(float deltaTime);
	void playShotSound();

	Animation stationary;
	Animation movingleft;
	Animation movingright;
	bool moving = false;
	bool facing_right = false;
	bool game_over = false;
	//stats
	unsigned magazine_curr = 5;
	float reloadTotalTime = 0.f;
	float shotGap = 0.2f;
	float shootTotalTime = 0.f;
	WeaponType curr_weapon = oneshot;
	unsigned curr_weapon_no = 4;
	unsigned lives = 1;
	const unsigned maxLives = 4;
	float speedMod = 1.f;
	const float maxSpeedMod = 2.f;
	float bulletSpeedMod = 1.f;
	const float maxBulletSpeedMod = 2.5f;
	float reloadTime = 0.75f;
	const float minReloadTime = 0.3f;
	unsigned magazineSize = 5;
	const unsigned maxMagazineSize = 15;
};



