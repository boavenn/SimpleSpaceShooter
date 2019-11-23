#include "Playing.hpp"

Playing::Playing(sf::RenderWindow& w, StateManager& sm) : State(w, sm)
{
	main_bg = new Background(0.06f, { 171.f, 0 }, "background");
}

Playing::~Playing()
{
	delete player;
	delete main_bg;
}

void Playing::update(float dt, sf::Event e)
{
	main_bg->update(dt);
	player->update(dt);
	if (player->isFiring())
	{
		std::vector<Projectile*> temp = player->getNewWeaponProjectiles();
		player_projectiles.insert(player_projectiles.end(), temp.begin(), temp.end());
	}

	for (Projectile* p : player_projectiles)
		p->update(dt);
}

void Playing::draw()
{
	main_bg->draw(window);
	player->draw(window);
	for (Projectile* p : player_projectiles)
		p->draw(window);
}

void Playing::checkInput(float dt, sf::Event e)
{

}
