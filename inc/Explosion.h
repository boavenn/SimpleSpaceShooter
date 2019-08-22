#pragma once
#include "Animation.h"
#include "ResourceManager.h"

class Explosion
{
public:
	Explosion(sf::Vector2f pos);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	int getCurrImg() { return explosion.getCurrImg(); }

private:
	void updateParticles(float deltaTime);

	Animation explosion;
	sf::Sprite sprite;
	sf::VertexArray particles;
	unsigned particles_size;
};

