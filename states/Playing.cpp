#include "Playing.hpp"

Playing::Playing(sf::RenderWindow& w, StateManager& sm) : State(w, sm)
{
	main_bg = new Background(0.06f, { 171.f, 0 }, "background");

	aliens.push_back(new Alien01(20.f, { 500.f, 200.f }));
	aliens.push_back(new Alien01(20.f, { 550.f, 200.f }));
	aliens.push_back(new Alien01(20.f, { 600.f, 200.f }));
	aliens.push_back(new Alien01(20.f, { 650.f, 200.f }));
	aliens.push_back(new Alien01(20.f, { 700.f, 200.f }));
	aliens.push_back(new Alien01(20.f, { 750.f, 200.f }));
}

Playing::~Playing()
{
	delete player;
	delete main_bg;
}

void Playing::update(float dt, sf::Event e)
{
	main_bg->update(dt);
	playerUpdates(dt);
	alienUpdates(dt);
}

void Playing::draw()
{
	main_bg->draw(window);
	player->draw(window);
	for (Projectile* p : player_projectiles)
		p->draw(window);
	for (Alien* a : aliens)
		a->draw(window);
}

void Playing::checkInput(float dt, sf::Event e)
{

}

void Playing::playerUpdates(float dt)
{
	player->update(dt);
	if (player->isFiring())
	{
		std::vector<Projectile*> temp = player->getNewWeaponProjectiles();
		player_projectiles.insert(player_projectiles.end(), temp.begin(), temp.end());
	}

	for (size_t i = 0; i < player_projectiles.size(); i++)
	{
		Projectile* proj = player_projectiles[i];
		proj->update(dt);
		if (proj->isOutOfMap())
			player_projectiles.erase(player_projectiles.begin() + i);
	}
}

void Playing::alienUpdates(float dt)
{
	for (Alien* a : aliens)
		a->update(dt);
}
