#pragma once
#include "../res/ResourceManager.hpp"

class FloatingText
{
public:
	FloatingText(const std::string info, sf::Vector2f pos, sf::Color c = sf::Color::White);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w) { w.draw(text); };
	bool isDead() { return died; };

private:
	sf::Text text;
	sf::Color color;
	bool died = false;
	float livingTime = 1.5f;
	float totalTime = 0.f;
	float totalMovementTime = 0.f;
	float movementTick = 0.2f;
};