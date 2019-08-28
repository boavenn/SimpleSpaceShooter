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
		plasma,
		permachain
	};

	friend class InfoDisplay;

public:
	Player();
	void input();
	void update(float deltaTime);
	bool isHit(std::vector<Projectile>& projectiles);
	bool gotPickup(std::vector<Pickup>& pickups);
	bool isChainingOn() { return chainingOn; };
	unsigned getLives() { return lives; };
	const unsigned long long& getKills() const { return kills; };
	const unsigned long long& getScore() const { return score; };
	const WeaponType& getWeaponType() { return curr_weapon; }
	float getBulletSpeedMod() { return bulletSpeedMod; };
	float getDmgMod() { return dmgMod; };
	void addKill() { kills++; };
	void addScore(unsigned points) { score += points; };

private:
	void checkReload(float deltaTime);
	void checkFiring(float deltaTime);
	void checkMovement(float deltaTime);
	void checkInvincibilty(float deltaTime);
	void checkChaining(float deltaTime);
	void playShotSound();
	void upgrade(Pickup::PickupType type);

	Animation stationary;
	Animation movingleft;
	Animation movingright;
	Animation stationaryInvinc;
	Animation movingleftInvinc;
	Animation movingrightInvinc;
	bool moving = false;
	bool facing_right = false;
	bool game_over = false;
	bool invincible = false;
	bool chainingOn = false;
	const float invincibiltyTime = 3.f;
	float invincibilityTotalTime = 0.f;
	float reloadTotalTime = 0.f;
	float shotGap = 0.2f;
	float shootTotalTime = 0.f;
	float chainingTotalTime = 0.f;
	const float chainingTime = 3.f;
	const unsigned maxLives = 4;
	unsigned magazine_curr = 5;
	//stats
	unsigned lives = 2;
	WeaponType curr_weapon = oneshot;
	unsigned curr_weapon_no = 1;
	float speedMod = 1.f;
	const float maxSpeedMod = 2.f;
	float bulletSpeedMod = 1.f;
	const float maxBulletSpeedMod = 3.f;
	float reloadTime = 0.62f;
	const float minReloadTime = 0.2f;
	unsigned magazineSize = 5;
	const unsigned maxMagazineSize = 15;
	float dmgMod = 1.f;
	unsigned long long kills = 0;
	unsigned long long score = 0;
};



