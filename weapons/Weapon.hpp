#pragma once
#include "../entities/Projectile.hpp"

class Player;

class Weapon
{
public:
	Weapon(Entity* entity);
	virtual std::vector<Projectile*> getNewProjectiles() = 0;

protected:
	Entity* entity;
};

