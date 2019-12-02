#pragma once
#include "../gui/Box.hpp"
#include "../entities/Player.hpp"
#include "../util/ValuesBar.hpp"

class HUD
{
public:
	HUD(Player* player);
	~HUD();
	void update(float dt);
	void draw(sf::RenderWindow& w);
	void setLevel(int level);

private:
	void init_boxes();
	void init_bars();

	Player* player;
	std::vector<sf::Sprite*> lives;

	ValuesBar* reload_time;
	ValuesBar* fire_rate;
	ValuesBar* speed;
	sf::Text* R;
	sf::Text* F;
	sf::Text* S;
	sf::Text* level;
	
	Box* money;
};