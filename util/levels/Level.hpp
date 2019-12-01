#pragma once
#include "../../entities/aliens/Alien1.hpp"
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