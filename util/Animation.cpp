#include "Animation.hpp"

Animation::Animation(float delay, bool loop)
{
	this->delay = delay;
	this->loop = loop;
}

void Animation::addFrame(const sf::IntRect& frame)
{
	frames.push_back(frame);
	if (current_frame_idx == -1)
	{
		current_frame_idx++;
		current_frame = frame;
	}
}

void Animation::resetAnimation()
{
	current_frame = frames.front();
	current_frame_idx = 0;
	animation_ended = false;
	elapsed = 0.f;
}

const sf::IntRect& Animation::update(float dt)
{
	elapsed += dt;
	if (elapsed >= delay)
	{
		elapsed -= delay;
		current_frame_idx++;

		if (animation_ended)
		{
			animation_ended = false;
			current_frame_idx = 0;
		}

		if (current_frame_idx >= frames.size() - 1)
			animation_ended = true;			
		
		if(loop)
			current_frame = frames[current_frame_idx];
		else if(!loop && !animation_ended)
			current_frame = frames[current_frame_idx];
	}
	return current_frame;
}

bool Animation::isAnimationEnded()
{
	return animation_ended;
}

const sf::IntRect& Animation::getFrameAt(unsigned idx)
{
	return frames[idx];
}

const sf::IntRect& Animation::getLastFrame()
{
	return frames.back();
}

const sf::IntRect& Animation::getFirstFrame()
{
	return frames.front();
}
