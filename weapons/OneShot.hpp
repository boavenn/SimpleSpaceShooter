#pragma once
#include "Weapon.hpp"

class OneShot : public Weapon
{
public:
	OneShot(Entity* entity);
	std::vector<Projectile*> getNewProjectiles(float v_mod) override;

private:
};

