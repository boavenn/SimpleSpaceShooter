#pragma once
#include "../res/ResourceManager.hpp"

class Background
{
public:
	Background(float switch_time, sf::Vector2f pos, std::string tex_name);
	void update(float dt);
	void draw(sf::RenderWindow& w);

private:
	sf::Sprite sprite;
	unsigned x_size;
	unsigned y_size;
	float timer = 0.f;
	float switch_time;
	int shift = 0;

// Getters and Setters
public:
	void setSwitchTime(float switch_time) { this->switch_time = switch_time; }
};

