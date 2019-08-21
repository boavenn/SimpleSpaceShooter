#pragma once
#include "Phantom.h"

class Enemy : public Phantom
{
public:
	Enemy(float shootingTime, float shootChance, unsigned type);
	void update(float deltaTime);
private:
	Animation movement;
	Animation gettingHit;
};

