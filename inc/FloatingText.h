#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class FloatingText
{
public:
	FloatingText(const std::string info, sf::Vector2f pos, sf::Color c = sf::Color::White);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w) { w.draw(text); };
	bool dead() { return died; };

private:
	sf::Text text;
	sf::Color color;
	bool died = false;
	bool is_white;
	float livingTime = 1.f;
	float totalTime = 0.f;
	float totalMovementTime = 0.f;
	float movementTick = 0.2f;
};

