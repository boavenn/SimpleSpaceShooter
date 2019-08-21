#pragma once
#include "Player.h"
#include "ResourceManager.h"
class ScreenManager
{
public:
	ScreenManager();
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
private:
	Player player;
};


