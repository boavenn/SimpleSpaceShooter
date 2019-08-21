#pragma once
#include "ResourceManager.h"
#include "Animation.h"

class Player
{
public:
	Player();
	void input();
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	void play(int buffer_no, float pitch, float vol);
	const sf::Vector2f& getPosition() const;
private:
	Animation stationary;
	Animation movingleft;
	Animation movingright;
	sf::Sprite sprite;
	sf::Vector2f velocity;
	std::vector<sf::SoundBuffer> buffer;
	std::vector<sf::Sound> sound;
	bool moving = false;
	bool facing_right = false;
	//stats
	unsigned magazine_size = 5;
	unsigned magazine_curr = 5;
	float reloadTime = 0.75f;
	float reloadTotalTime = 0.f;
	float shotGap = 0.25f;
	float shootTotalTime = 0.f;
};



