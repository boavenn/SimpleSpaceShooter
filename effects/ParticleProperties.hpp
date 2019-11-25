#pragma once
#include "SFML/Graphics.hpp"

class ParticleProperties
{
public:
	ParticleProperties(sf::Vector2f velocity, sf::Vector2f acc);
	void update(float dt);

private:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

public:
	sf::Vector2f getVelocity() { return velocity; }
};