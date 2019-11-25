#pragma once
#include "../util/Animation.hpp"
#include "../res/ResourceManager.hpp"
#include "Effect.hpp"

class Explosion : public Effect
{
public:
	Explosion(sf::Vector2f pos, float max_life_time, int type);
	void update(float dt);
	void draw(sf::RenderWindow& w);

private:
	sf::Sprite sprite;
	Animation* animation;
};