#pragma once
#include "../entities/Projectile.hpp"

class Player;

class Weapon
{
public:
	Weapon(Player* player);
	virtual std::vector<Projectile*> getNewProjectiles() = 0;

protected:
	Player* player;
};

