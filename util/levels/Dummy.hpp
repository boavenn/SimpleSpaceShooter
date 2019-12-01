#pragma once
#include "../entities/Entity.hpp"
#include "../res/ResourceManager.hpp"

class Dummy : public Entity
{
public:
	Dummy(std::string tex, sf::IntRect rect, int type, sf::Vector2f pos);
	Dummy(Dummy* d);
	void update(float dt) override {}
	void draw(sf::RenderWindow& w) override { w.draw(sprite); };
	void setPosition(sf::Vector2f pos) { sprite.setPosition(pos); }
	bool isActive(sf::RenderWindow& w);
	void setDirection(int dir) { direction = dir; }
	void setDelay(float delay) { this->delay = delay; }

	std::string tex;
	sf::IntRect rect;
	int type;
	int direction = 4;
	float delay = 0.0f;
	bool is_active = false;
};