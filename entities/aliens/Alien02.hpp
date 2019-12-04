#pragma once
#include "Alien.hpp"

class Alien02 : public Alien
{
public:
	Alien02(sf::Vector2f pos, int direction, float delay, float hp);
	void update(float dt) override;
	void draw(sf::RenderWindow& w) override;
	std::vector<Projectile*> getProjectiles();

private:
};