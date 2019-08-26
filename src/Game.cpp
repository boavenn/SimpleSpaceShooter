#include "..\inc\Game.h"

Game::Game() : window({ 1366,768,32 }, "SimpleSpaceShooter")
{
	font.loadFromFile("res/fonts/VCR_OSD_MONO_1.001.ttf");
	sprite.setTexture(ResourceManager::get().textures.get("gameover"));
	sprite.setOrigin({ 250.f, 150.f });
	sprite.setPosition({ 683.f, 384.f });
	loadText();
}

void Game::run()
{ 
	do
	{
		screen_manager = new ScreenManager;
		shouldrestart = false;
		sf::Clock clock;

		while (window.isOpen() && !screen_manager->game_over)
		{
			checkEvents();
			update(clock.restart().asSeconds());
			window.clear();
			draw();
			window.display();
		}

		loadStats(screen_manager->getPlayer().getKills(), screen_manager->getPlayer().getScore());

		while (screen_manager->game_over)
		{
			gameoverScreen();
			if (!window.isOpen())
				shouldexit = true;

			if (shouldexit || shouldrestart)
				break;
		}

	} while (shouldrestart && window.isOpen());

}

void Game::gameoverInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		shouldexit = true;
		delete screen_manager;
		screen_manager = nullptr;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		shouldrestart = true;
		delete screen_manager;
		screen_manager = nullptr;
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

void Game::gameoverScreen()
{
	window.draw(sprite);

	for (unsigned i = 0; i < text.size(); i++)
		window.draw(text[i]);

	gameoverInput();
	checkEvents();
	window.display();
}

void Game::update(float deltaTime)
{
	screen_manager->update(deltaTime);
}

void Game::draw()
{
	screen_manager->draw(window);
}

void Game::loadStats(unsigned long long  player_kills, unsigned long long player_score)
{
	std::string kills = std::to_string(player_kills);
	std::string score = std::to_string(player_score);

	text[1].setString("SCORE: " + score);
	text[2].setString("KILLS: " + kills);
}

void Game::loadText()
{
	sf::Text t;
	t.setFont(font);
	t.setFillColor(sf::Color::White);
	t.setCharacterSize(50);

	t.setPosition(575.f, 240.f);
	t.setString("YOU LOST");
	text.push_back(t);

	t.setCharacterSize(30);
	t.setPosition(450.f, 340.f);
	t.setString("SCORE:");
	text.push_back(t);

	t.setPosition(450.f, 370.f);
	t.setString("KILLS:");
	text.push_back(t);

	t.setCharacterSize(20);
	t.setPosition(450.f, 450.f);
	t.setString("PRESS ESC TO QUIT");
	text.push_back(t);

	t.setPosition(450.f, 470.f);
	t.setString("PRESS LCTRL TO RESTART");
	text.push_back(t);
}
