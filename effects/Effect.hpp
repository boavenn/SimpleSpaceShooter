#pragma once
#include <SFML/Graphics.hpp>

class Effect
{
public:
	Effect(sf::Vector2f pos, float max_life_time) : position(pos), max_life_time(max_life_time) {}
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& w) = 0;
	bool shouldDie() { return should_die; }

protected:
	sf::Vector2f position;
	bool should_die = false;
	float max_life_time;
	float life_timer = 0.f;
};