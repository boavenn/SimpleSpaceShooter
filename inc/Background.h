#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Background
{
public:
	Background(float switchTime, sf::Vector2f pos, const std::string texName, bool fromRight = 0);
	void update(float deltaTime);
	void changeSwitchTime(float time) { switchTime -= time; }
	void draw(sf::RenderWindow& w) { w.draw(sprite); }

private:
	sf::Sprite sprite;
	bool fromRight;
	unsigned xSize;
	unsigned ySize;
	float totalTime = 0.f;
	float switchTime = 0;
	int shift = 0;
};

