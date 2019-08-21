#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenManager.h"
class Game
{
public:
	Game();
	void run();

private:
	void checkEvents();
	void update(float deltaTime);
	void draw();

	sf::RenderWindow window;
	ScreenManager screen_manager;
};
