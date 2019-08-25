#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Player.h"

class InfoDisplay
{
public:
	InfoDisplay();
	void updateInfo(const Player& player);
	void draw(sf::RenderWindow& w);

private:
	void addInfo();

	std::vector<sf::Font> fonts;
	std::vector<sf::Text> infos;
};

