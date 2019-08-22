#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(sf::IntRect startingFrame, unsigned imgCount, float delay, bool is_looped);
	const sf::IntRect& update(float deltaTime);
	unsigned getCurrImg() const { return currentImg; }

private:
	sf::IntRect currentFrame;
	sf::IntRect startingFrame;
	const unsigned imgCount;
	const float delay;
	const int width;
	const int height;
	float totalTime = 0.f;
	int currentImg = 0;
	bool is_looped;
};

