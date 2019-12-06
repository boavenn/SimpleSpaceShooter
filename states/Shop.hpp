#pragma once
#include "StateManager.hpp"
#include "../gui/Button.hpp"
#include "../entities/Player.hpp"
#include "../util/HUD.hpp"
#include <unordered_map>

class Shop : public State, public SoundMaking
{
public:
	Shop(sf::RenderWindow& w, StateManager& sm, Player* player, int level);
	~Shop();
	void update(float dt, sf::Event e);
	void draw();
	void checkInput(float dt, sf::Event e);

private:
	void init_options();

	Player* player;
	std::vector<Button*> options;
	std::vector<Box*> price_boxes;
	Button* quit;
	int util_quantity = 6;
	int weapon_quantity = 4;
	HUD* hud;
	sf::Sprite background;
	sf::Sprite sidebar_l;
	sf::Sprite sidebar_r;
	std::unordered_map<std::string, int> prices;
};