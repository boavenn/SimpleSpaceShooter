#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
public:
	Animation(sf::IntRect startingFrame, unsigned imgCount, float delay);
	sf::IntRect& update(float deltaTime);

private:
	sf::IntRect currentFrame;
	sf::IntRect startingFrame;
	const unsigned imgCount;
	const float delay;
	const int width;
	const int height;
	float totalTime = 0.f;
	unsigned currentImg = 0;
};

