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
	Animation explosion;
	sf::Sprite sprite;
};

