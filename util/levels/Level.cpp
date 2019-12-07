#include "Level.hpp"

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
	float base_delay = 1.f;
	float d = delay + base_delay;
	switch (type)
	{
	case 1:
		temp = new Alien01(pos, direction, d, 5.f);
		break;
	case 2:
		temp = new Alien02(pos, direction, d, 10.f);
		break;
	case 3:
		temp = new Alien03(pos, direction, d, 15.f);
		break;
	case 4:
		temp = new Alien04(pos, direction, d, 20.f);
		break;
	case 5:
		temp = new Alien05(pos, direction, d, 20.f);
		break;
	default:
		temp = new Alien01(pos, direction, d, 5.f);
		break;
	}
	return temp;
}
