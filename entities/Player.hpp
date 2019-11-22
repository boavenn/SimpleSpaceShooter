#pragma once

#include <unordered_map>
#include "../util/Animation.hpp"
#include "../res/ResourceManager.hpp"

class Player
{
public:
	Player();
	void input();
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);

private:
	std::unordered_map<std::string, Animation*> animations;
	sf::Sprite sprite;
};

