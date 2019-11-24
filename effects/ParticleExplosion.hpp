#pragma once
#include "ParticleProperties.hpp"
#include "../util/Random.hpp"

class ParticleExplosion
{
public:
	ParticleExplosion(sf::Vector2f pos, unsigned size, float max_life_time);
	~ParticleExplosion();
	void update(float dt);
	void draw(sf::RenderWindow& w);
	bool shouldDie() { return should_die; }

private:
	std::pair<std::vector<ParticleProperties*>, sf::VertexArray*> particles;
	bool should_die = false;
	float max_life_time;
	float life_timer = 0.f;
};