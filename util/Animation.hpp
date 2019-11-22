#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(float delay);
	
	const sf::IntRect& update(float dt);

	void addFrame(const sf::IntRect& frame);
	void resetAnimation();
	bool isAnimationEnded();

	const sf::IntRect& getFrameAt(unsigned idx);
	const sf::IntRect& getLastFrame();
	const sf::IntRect& getFirstFrame();

private:
	float delay;
	float elapsed = 0.f;
	bool animation_ended = false;
	int current_frame_idx = -1;
	sf::IntRect current_frame;
	std::vector<sf::IntRect> frames;
};

