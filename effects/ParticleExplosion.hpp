#pragma once
#include "ParticleProperties.hpp"
#include "../util/Random.hpp"
#include "Effect.hpp"

class ParticleExplosion : public Effect
{
public:
	ParticleExplosion(sf::Vector2f pos, float max_life_time, unsigned size);
	~ParticleExplosion();
	void update(float dt);
	void draw(sf::RenderWindow& w);

private:
	std::pair<std::vector<ParticleProperties*>, sf::VertexArray*> particles;
};