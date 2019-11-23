#pragma once
#include <SFML/Graphics.hpp>
#include "../util/WindowProperties.hpp"

class StateManager;

class State
{
public:
	State(sf::RenderWindow& w, StateManager& sm) : window(w), state_manager(sm) {}
	virtual void update(float dt, sf::Event e) = 0;
	virtual void draw() = 0;
	virtual void checkInput(float dt, sf::Event e) = 0;
	void setPlace(unsigned idx);
	bool& isConcurrent();

protected:
	bool isAbleToInput(float dt);

	float transition_freeze_time = 0.2f;
	float transition_elapsed = 0.f;
	bool input_ability = false;
	bool is_concurrent = false;
	bool should_pop = false;
	unsigned place_on_stack = 0;
	sf::RenderWindow& window;
	StateManager& state_manager;
};

