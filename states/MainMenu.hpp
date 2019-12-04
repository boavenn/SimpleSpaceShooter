#pragma once
#include "StateManager.hpp"
#include "../gui/Button.hpp"
#include "Playing.hpp"
#include "LevelEditor.hpp"

class MainMenu : public State, public SoundMaking
{
public:
	MainMenu(sf::RenderWindow& w, StateManager& sm);
	~MainMenu();
	void update(float dt, sf::Event e);
	void draw();
	void checkInput(float dt, sf::Event e);

private:
	void init_buttons();
	bool gained_focus = false;

	std::vector<Button*> buttons;
	sf::Sprite background;
};