#pragma once
#include "Weapon.hpp"

class DoubleShot : public Weapon
{
public:
	DoubleShot(Entity* entity);
	std::vector<Projectile*> getNewProjectiles(float v_mod) override;

private:
};

