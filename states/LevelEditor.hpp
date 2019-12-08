#pragma once
#include "StateManager.hpp"
#include <fstream>
#include "../util/Background.hpp"
#include "../entities/Entity.hpp"
#include "../res/ResourceManager.hpp"
#include "../util/levels/Dummy.hpp"
#include "../util/WindowProperties.hpp"
#include "../gui/InputButton.hpp"

class LevelEditor : public State
{
public:
	LevelEditor(sf::RenderWindow& w, StateManager& sm);
	~LevelEditor();
	void update(float dt, sf::Event e);
	void draw();
	void checkInput(float dt, sf::Event e);

private:
	void saveToFile(std::string filename);
	void init_lines();
	void init_dummies();
	void init_setters();
	void init_instructions();

	std::vector<Dummy*> dummies;
	Dummy* active_dummy = nullptr;
	bool copy_active = false;
	bool delete_active = false;
	bool saving = false;

	float dir_change_timer = 0.f;
	float dir_change_gap = 0.1f;

	std::vector<sf::RectangleShape*> lines;
	InputButton* setter;
	InputButton* saver;
	bool setter_visible = false;
	bool saver_visible = false;

	Background* main_bg;
	Background* layer1;
	sf::Sprite sidebar_l;
	sf::Sprite sidebar_r;

	std::vector<Box*> instructions;
};