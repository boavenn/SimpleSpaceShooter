#include "Level.hpp"
#include <iostream>

Level::Level(int level)
{
	this->level = level;
}

Level::~Level()
{
	for (size_t i = 0; i < aliens.size(); i++)
	{
		delete aliens[i];
	}
	aliens.clear();
}

std::vector<Alien*> Level::loadFromFile()
{
	std::string line;
	std::ifstream file("LevelConfig/level" + std::to_string(level) + ".txt");
	std::stringstream ss;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			ss << line;
			int type;
			int dir;
			float pos_x;
			float pos_y;
			float delay;
			char sep;
			ss >> type >> sep >> dir >> sep >> delay >> sep >> pos_x >> sep >> pos_y;
			ss.clear();
			aliens.push_back(createNewAlien(type, { pos_x, pos_y }, dir, delay));
		}
		file.close();
	}
	return aliens;
}

Alien* Level::createNewAlien(int type, sf::Vector2f pos, int direction, float delay)
{
	Alien* temp;
	switch (type)
	{
	case 1:
		temp = new Alien1(pos, direction, delay);
		break;
	default:
		temp = new Alien1(pos, direction, delay);
		break;
	}
	return temp;
}
