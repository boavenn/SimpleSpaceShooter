#include "ParticleExplosion.hpp"
#include <iostream>

typedef Random R;

ParticleExplosion::ParticleExplosion(sf::Vector2f pos, unsigned size, float max_life_time)
{
	this->max_life_time = max_life_time;

	particles.second = new sf::VertexArray(sf::PrimitiveType::Points, size);
	for (size_t i = 0; i < size; i++)
	{
		particles.first.push_back(new ParticleProperties({ R::nextFloat(-200, 200), R::nextFloat(-200, 200) }, { R::nextFloat(-100, 100), R::nextFloat(-100, 100) }));
		(*particles.second)[i].position = pos;
		(*particles.second)[i].color = sf::Color(R::nextInt(200, 255), R::nextInt(0, 255), R::nextInt(0, 60));
	}
}

ParticleExplosion::~ParticleExplosion()
{
	for (size_t i = 0; i < particles.first.size(); i++)
		delete particles.first[i];
	delete particles.second;
}

void ParticleExplosion::update(float dt)
{
	for (size_t i = 0; i < particles.second->getVertexCount(); i++)
	{
		particles.first[i]->update(dt);
		(*particles.second)[i].position.x += particles.first[i]->getVelocity().x * dt;
		(*particles.second)[i].position.y += particles.first[i]->getVelocity().y * dt;
		if(life_timer < max_life_time)
			(*particles.second)[i].color.a = 255 - 255 * life_timer / max_life_time;
	}

	life_timer += dt;
	if (life_timer >= max_life_time)
		should_die = true;
}

void ParticleExplosion::draw(sf::RenderWindow& w)
{
	if (!should_die)
		w.draw(*particles.second);	
}
