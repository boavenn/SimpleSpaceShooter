#pragma once
#include "Phantom.h"

class Enemy : public Phantom
{
public:
	Enemy(float shototingDelay, float shootingChance, unsigned type);
	void update(float deltaTime);
	const unsigned& getType() { return type; }
private:
	Animation movement;
	Animation gettingHit;
	//stats
	float shootingDelay; // time between every consecutive shooting try
	float shootingChance;
	unsigned type;
};

