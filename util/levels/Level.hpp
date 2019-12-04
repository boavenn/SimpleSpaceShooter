#pragma once
#include "../../entities/aliens/Alien01.hpp"
#include "../../entities/aliens/Alien02.hpp"
#include "../../entities/aliens/Alien03.hpp"
#include "../../entities/aliens/Alien04.hpp"
#include <fstream>
#include <sstream>

class Level
{
public:
	Level(int level);
	~Level();
	std::vector<Alien*> loadFromFile();

private:
	Alien* createNewAlien(int type, sf::Vector2f pos, int direction, float delay);

	std::vector<Alien*> aliens;
	int level;

public:
	int getLevel() { return level; }
};