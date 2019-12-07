#pragma once
#include "StateManager.hpp"
#include "..//gui/Button.hpp"
#include <fstream>

class HighScores : public State
{
public:
	HighScores(sf::RenderWindow& w, StateManager& sm);
	~HighScores();
	void update(float dt, sf::Event e);
	void draw();
	void checkInput(float dt, sf::Event e);

private:
	void loadScores();
	void sortScores();
	void putScoresInBoxes();

	std::vector<Box*> scores_b;
	std::vector<Box*> names_b;
	Button* quit;
	std::vector<std::pair<int, std::string>> scores;
};