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
	void shouldDisplayLives(bool b) { should_display_lives = b; }

private:
	void init_boxes();
	void init_bars();

	Player* player;
	std::vector<sf::Sprite*> lives;
	bool should_display_lives = true;

	ValuesBar* reload_time;
	ValuesBar* fire_rate;
	ValuesBar* speed;
	ValuesBar* proj_speed;
	sf::Text* R;
	sf::Text* F;
	sf::Text* S;
	sf::Text* BS;
	sf::Text* level;
	
	Box* money;
	Box* score;
};