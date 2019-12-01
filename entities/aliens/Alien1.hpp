#pragma once
#include "Alien.hpp"

class Alien1 : public Alien
{
public:
	Alien1(sf::Vector2f pos, int direction);
	void update(float dt) override;
	void draw(sf::RenderWindow& w) override;
	std::vector<Projectile*> getProjectiles();

private:
};