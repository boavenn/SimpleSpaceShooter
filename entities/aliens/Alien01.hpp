#pragma once
#include "Alien.hpp"

class Alien01 : public Alien
{
public:
	Alien01(float max_health, sf::Vector2f pos);
	void update(float dt) override;
	void draw(sf::RenderWindow& w) override;
	bool isHitBy(Projectile* proj) override;

private:

};