#pragma once
#include "../res/ResourceManager.hpp"

class ValuesBar
{
public:
	ValuesBar(float min, float max, std::string tex, sf::IntRect rect, sf::Vector2f pos);
	void update(float current);
	void draw(sf::RenderWindow& w);

private:
	sf::Sprite* bar;
	sf::RectangleShape background;
	float max;
	float min;
	sf::IntRect rect;
};