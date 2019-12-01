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

	std::vector<Dummy*> dummies;
	Dummy* active_dummy = nullptr;
	bool copy_active = false;
	bool delete_active = false;
	bool saving = false;

	std::vector<sf::RectangleShape*> lines;
	InputButton* dir_setter;
	InputButton* saver;
	bool dir_setter_visible = false;
	bool saver_visible = false;

	Background* main_bg;
	Background* layer1;
};