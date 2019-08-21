#include "..\inc\Game.h"

Game::Game() : window({ 1366,768,32 }, "StarShooter")
{

}

void Game::run()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		checkEvents();
		update(clock.restart().asSeconds());
		window.clear();
		draw();
		window.display();
	}
}

void Game::checkEvents()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			window.close();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
	}
}

void Game::update(float deltaTime)
{
	screen_manager.update(deltaTime);
}

void Game::draw()
{
	screen_manager.draw(window);
}
