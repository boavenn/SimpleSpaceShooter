#pragma once
#include "Weapon.hpp"

class DoubleShot : public Weapon
{
public:
	DoubleShot(Entity* entity);
	std::vector<Projectile*> getNewProjectiles(float dmg_mod) override;

private:
};

