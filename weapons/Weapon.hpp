#pragma once
#include "../entities/Projectile.hpp"

class Player;

class Weapon
{
public:
	Weapon(Entity* entity);
	virtual std::vector<Projectile*> getNewProjectiles(float v_mod = 1.f) = 0;

protected:
	Entity* entity;
	float base_dmg = 0;
};

