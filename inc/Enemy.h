#pragma once
#include "Phantom.h"
#include "Random.h"

class Enemy : public Phantom
{
public:
	Enemy(float maxHealth, float shototingDelay, float shootingChance, unsigned type, sf::Vector2f pos);
	void update(float deltaTime);
	const unsigned& getType() { return type; }

private:
	void tryFire(float deltaTime);
	void playShotSound();
	sf::IntRect getMovRect(unsigned type);
	sf::IntRect getHitRect(unsigned type);

	Animation movement;
	Animation gettingHit;
	Random rand;
	//stats
	float shootingDelay; // time between every consecutive shooting try
	float shootingChance;
	float shootingTotalTime = 0.f;
	unsigned type;
};

