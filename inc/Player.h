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

	friend class InfoDisplay;

public:
	Player();
	void input();
	void update(float deltaTime);
	bool gotPickup(std::vector<Pickup>& pickups);
	void upgrade(Pickup::PickupType type);
	const WeaponType& shoot() { return curr_weapon; }
	float getBulletSpeedMod() { return bulletSpeedMod; };
	const unsigned long long& getKills() const { return kills; };
	const unsigned long long& getScore() const { return score; };
	void addKill() { kills++; };
	void addScore(unsigned points) { score += points; };
	unsigned getLives() { return lives; };

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
	unsigned magazine_curr = 5;
	float reloadTotalTime = 0.f;
	float shotGap = 0.2f;
	float shootTotalTime = 0.f;
	const unsigned maxLives = 4;
	//stats
	WeaponType curr_weapon = oneshot;
	unsigned curr_weapon_no = 1;
	float speedMod = 1.f;
	const float maxSpeedMod = 2.f;
	float bulletSpeedMod = 1.f;
	const float maxBulletSpeedMod = 2.5f;
	float reloadTime = 0.75f;
	const float minReloadTime = 0.3f;
	unsigned magazineSize = 5;
	const unsigned maxMagazineSize = 15;
	unsigned long long kills = 0;
	unsigned long long score = 0;
};



