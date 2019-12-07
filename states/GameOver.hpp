#pragma once
#include "StateManager.hpp"
#include "../gui/InputButton.hpp"
#include <fstream>

class GameOver : public State
{
public:
	GameOver(sf::RenderWindow& w, StateManager& sm, long score);
	~GameOver();
	void update(float dt, sf::Event e);
	void draw();
	void checkInput(float dt, sf::Event e);
private:
	void addScoreToFile();

	sf::Sprite background;
	sf::Text gameover;
	Box* enter_name;
	InputButton* nickname_box;
	unsigned score;
};