#pragma once
#include "ResourceManager.h"
#include "Animation.h"
class Phantom
{
public:
	Phantom(unsigned max_sounds) : sound(max_sounds) {}
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& w) { w.draw(sprite); }
	virtual void play(int buffer_no, float pitch, float vol);
	virtual const sf::Vector2f& getPosition() { return sprite.getPosition(); }
	virtual const bool& isShooting() { return try_shoot; }
protected:
	sf::Sprite sprite;
	sf::Vector2f velocity;
	std::vector<sf::SoundBuffer> buffer;
	std::vector<sf::Sound> sound;
	bool try_shoot = false;
};

