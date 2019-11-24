#include "Playing.hpp"

Playing::Playing(sf::RenderWindow& w, StateManager& sm) : State(w, sm)
{
	main_bg = new Background(0.06f, { 171.f, 0 }, "background");

	for (int i = 0; i < 5; i++)
	{
		aliens.push_back(new Alien01(20.f, { 500.f, 200.f + 50 * i }));
		aliens.push_back(new Alien01(20.f, { 570.f, 200.f + 50 * i }));
		aliens.push_back(new Alien01(20.f, { 640.f, 200.f + 50 * i }));
		aliens.push_back(new Alien01(20.f, { 710.f, 200.f + 50 * i }));
		aliens.push_back(new Alien01(20.f, { 780.f, 200.f + 50 * i }));
		aliens.push_back(new Alien01(20.f, { 850.f, 200.f + 50 * i }));
	}
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
	effectUpdates(dt);
}

void Playing::draw()
{
	main_bg->draw(window);
	for (ParticleExplosion* pe : particle_explosions)
		pe->draw(window);
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
	for (size_t i = 0; i < aliens.size(); i++)
	{
		Alien* alien = aliens[i];

		for (size_t j = 0; j < player_projectiles.size(); j++)
		{
			if(alien->gotHitBy(player_projectiles[j]))
				player_projectiles.erase(player_projectiles.begin() + j);
		}
		alien->update(dt);
		if (alien->shouldDie())
		{
			particle_explosions.push_back(new ParticleExplosion(alien->getPosition(), 100, R::nextFloat(2, 7)));
			aliens.erase(aliens.begin() + i);
			i--;		
		}
	}
}

void Playing::effectUpdates(float dt)
{
	for (size_t i = 0; i < particle_explosions.size(); i++)
	{
		particle_explosions[i]->update(dt);
		if (particle_explosions[i]->shouldDie())
		{
			delete particle_explosions[i];
			particle_explosions.erase(particle_explosions.begin() + i);
			i--;
		}
	}
}
