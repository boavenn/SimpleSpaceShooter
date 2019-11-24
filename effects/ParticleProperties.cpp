#include "ParticleProperties.hpp"

ParticleProperties::ParticleProperties(sf::Vector2f velocity, sf::Vector2f acc)
{
	this->velocity = velocity;
	acceleration = acc;
}

void ParticleProperties::update(float dt)
{
	velocity += acceleration * dt;
}
