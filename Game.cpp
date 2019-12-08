#include "Game.hpp"
#include <thread>
#include <chrono>
#include <iostream>

Game::Game() : window(sf::VideoMode(WindowProperties::getWidth(), WindowProperties::getHeight(), 32), "Simple Space Shooter", sf::Style::None | sf::Style::Close)
{
	window.setFramerateLimit(60);
	fps = new Box({ 30, 20 }, { 6, 10 });
	fps->setFont("MonospaceTypewriter");
	fps->setText("0");
	fps->setMainIdleColor(sf::Color::Black);
	fps->setTextIdleColor(sf::Color::Green);

	state_manager.pushState(std::make_unique<MainMenu>(window, state_manager), 0, 1);
}

Game::~Game()
{
	delete fps;
}

void Game::run()
{
	sf::Clock clock;
	sf::Event e;

	int counter = 0;

	sf::Clock fps_clock;
	fps_clock.restart().asSeconds();

	while (window.isOpen() && !state_manager.isEmpty())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}
		update(clock.restart().asSeconds(), e);
		draw();

		if (fps_clock.getElapsedTime().asSeconds() >= 1.f)
		{
			fps->setText(std::to_string(counter));
			counter = 0;
			fps_clock.restart().asSeconds();
		}
		counter++;
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
	fps->draw(window);
	window.display();
}
