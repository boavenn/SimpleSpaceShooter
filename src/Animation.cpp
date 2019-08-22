#include "..\inc\Animation.h"

Animation::Animation(sf::IntRect startingFrame, unsigned imgCount, float delay, bool is_looped)
	: delay{ delay }, imgCount{ imgCount }, width{ startingFrame.width }, height{ startingFrame.height }, startingFrame{startingFrame}
{
	this->is_looped = is_looped;
	currentFrame = startingFrame;
}

const sf::IntRect& Animation::update(float deltaTime)
{
	if (currentImg == -1)  // it may seem weird, but by doing that we can tell whether one and only loop of animation has ended or not, and,
		currentImg = 0;	   // that's important, we may reuse it later if we need to because currentImg is 0 again
	totalTime += deltaTime;
	if (totalTime >= delay)
	{
		totalTime -= delay;
		currentFrame.left += abs(width);
		currentImg++;
		if (currentImg >= int(imgCount))
		{
			if (is_looped)
			{
				currentFrame = startingFrame;
				currentImg = 0;
			}
			else
			{
				currentFrame = startingFrame;
				currentImg = -1;
			}
		}
	}
	return currentFrame;
}