#include "..\inc\Animation.h"

Animation::Animation(sf::IntRect startingFrame, unsigned imgCount, float delay)
	: delay{ delay }, imgCount{ imgCount }, width{ startingFrame.width }, height{ startingFrame.height }
{
	this->startingFrame = startingFrame;
	currentFrame = startingFrame;
}

const sf::IntRect& Animation::update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= delay)
	{
		totalTime -= delay;
		currentFrame.left += abs(width);
		currentImg++;
		if (currentImg >= imgCount)
		{
			currentFrame = startingFrame;
			currentImg = 0;
		}
	}
	return currentFrame;
}