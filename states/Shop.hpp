#pragma once
#include "StateManager.hpp"
#include "../gui/Button.hpp"
#include "../entities/Player.hpp"
#include "../effects/ParticleExplosion.hpp"
#include "../util/HUD.hpp"
#include "../util/Random.hpp"
#include <unordered_map>

typedef Random R;

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
	std::vector<ParticleExplosion*> explosions;
	float explosion_add_interval = 0.1f;
	float explosion_timer = 0.f;

	Button* quit;
	int util_quantity = 6;
	int weapon_quantity = 4;
	HUD* hud;
	sf::Sprite background;
	sf::Sprite sidebar_l;
	sf::Sprite sidebar_r;
	std::unordered_map<std::string, int> prices;
};