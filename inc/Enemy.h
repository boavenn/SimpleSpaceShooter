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
	void updateMovement(float deltaTime);
	sf::IntRect getMovRect(unsigned type);
	sf::IntRect getHitRect(unsigned type);

	Animation movement;
	Animation gettingHit;
	Random rand;
	bool try_go_up = false;
	bool turning_right = false;
	float movementTotalTime = 0.f;
	float movementTick = 0.8f;
	float turningTotalTime = 0.f;
	float turningTick = 2.f;
	//stats
	float shootingDelay; // time between every consecutive shooting try
	float shootingChance;
	float shootingTotalTime = 0.f;
	float maxDepth;
	unsigned type;
};

