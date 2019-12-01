#pragma once
#include "states/MainMenu.hpp"
#include "util/WindowProperties.hpp"
#include "gui/Box.hpp"

class Game
{
public:
	Game();
	void run();

private:
	void update(float dt, sf::Event e);
	void draw();

	sf::RenderWindow window;
	StateManager state_manager;
	Box* fps;
};

