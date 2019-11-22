#include "Game.hpp"

Game::Game() : window(sf::VideoMode(1366, 768, 32), "Simple Space Shooter", sf::Style::None | sf::Style::Close)
{
	// Here the first state like MainMenu should be pushed to StateManager
	// state_manager.pushState(std::make_unique<FirstState>(window, state_manager), 0, 1)
	state_manager.pushState(std::make_unique<Playing>(window, state_manager), 0, 1);
}

void Game::run()
{
	sf::Clock clock;
	sf::Event e;
	while (window.isOpen() && !state_manager.isEmpty())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}
		update(clock.restart().asSeconds(), e);
		draw();
	}
}

void Game::update(float dt, sf::Event e)
{
	state_manager.getTop().update(dt, e);
}

void Game::draw()
{
	window.clear();
	if (!state_manager.isEmpty())
		state_manager.getTop().draw();
	window.display();
}
