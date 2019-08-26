#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenManager.h"
#include "ResourceManager.h"

class Game
{
public:
	Game();
	void run();

private:
	void checkEvents();
	void gameoverScreen();
	void update(float deltaTime);
	void draw();

	ScreenManager* screen_manager = nullptr;
	bool shouldexit = false;
	bool shouldrestart = false;
	sf::RenderWindow window;

	//gameover screen, poor idea to implement it here
	void gameoverInput();
	void loadText();
	void loadStats(unsigned long long player_kills, unsigned long long player_score);

	sf::Sprite sprite;
	sf::Font font;
	std::vector<sf::Text> text;

};
