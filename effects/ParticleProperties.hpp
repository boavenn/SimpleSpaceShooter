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
	sf::Uint8 alfa = 255;

public:
	sf::Vector2f getVelocity() { return velocity; }
	sf::Uint8 getAlfa() { return alfa; }
	void setAlfa(sf::Uint8 a) { alfa = a; }
};