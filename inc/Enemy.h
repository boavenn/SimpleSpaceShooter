#pragma once
#include "Phantom.h"
#include <random>
#include <chrono>

class Enemy : public Phantom
{
public:
	Enemy(float maxHealth, float shototingDelay, float shootingChance, unsigned type, sf::Vector2f pos);
	void update(float deltaTime);
	const unsigned& getType() { return type; }

private:
	void tryFire(float deltaTime);

	Animation movement;
	Animation gettingHit;
	//stats
	float shootingDelay; // time between every consecutive shooting try
	float shootingChance;
	float shootingTotalTime = 0.f;
	unsigned type;
};

