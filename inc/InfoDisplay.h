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
	void addPickupInfo();

	sf::Sprite heart;
	unsigned lives_left;
	std::vector<sf::Sprite> pickup_sprites;
	std::vector<sf::Font> fonts;
	std::vector<sf::Text> infos;
};

