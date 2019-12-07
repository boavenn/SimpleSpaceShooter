#pragma once
#include "../entities/Projectile.hpp"

class Player;

class Weapon
{
public:
	Weapon(Entity* entity, std::string sound);
	virtual std::vector<Projectile*> getNewProjectiles(float v_mod = 1.f) = 0;
	std::string getSound() { return sound; }

protected:
	Entity* entity;
	std::string sound;
	float base_dmg = 0;
};

