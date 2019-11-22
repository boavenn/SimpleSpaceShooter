#pragma once
#include "StateManager.hpp"
#include "../entities/Player.hpp"

class Playing : public State
{
public:
	Playing(sf::RenderWindow& w, StateManager& sm);
	~Playing();
	void update(float dt, sf::Event e);
	void draw();
	void checkInput(float dt, sf::Event e);

private:
	Player* player = new Player();
};

