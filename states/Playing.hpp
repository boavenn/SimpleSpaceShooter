#pragma once
#include "StateManager.hpp"
#include "../entities/Player.hpp"
#include "../entities/Projectile.hpp"
#include "../util/Background.hpp"
#include "../weapons/OneShot.hpp"
#include "../entities/aliens/Alien01.hpp"

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
	std::vector<Projectile*> player_projectiles;

	std::vector<Alien*> aliens;
	std::vector<Projectile*> alien_projectiles;

	Background* main_bg;

private:
	void playerUpdates(float dt);
	void alienUpdates(float dt);
};

