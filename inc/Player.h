#pragma once
#include "Phantom.h"

class Player : public Phantom
{
public:
	enum WeaponType
	{
		oneshot = 1
	};

public:
	Player();
	void input();
	void update(float deltaTime);
	const WeaponType& shoot() { return curr_weapon; }

private:
	void tryReload(float deltaTime);
	void tryFire(float deltaTime);
	void checkMovement(float deltaTime);

	Animation stationary;
	Animation movingleft;
	Animation movingright;
	bool moving = false;
	bool facing_right = false;
	//stats
	unsigned magazine_size = 5;
	unsigned magazine_curr = 5;
	float reloadTime = 0.75f;
	float reloadTotalTime = 0.f;
	float shotGap = 0.25f;
	float shootTotalTime = 0.f;
	WeaponType curr_weapon = oneshot;
	unsigned curr_weapon_no = 1;
	unsigned lives = 1;
};



