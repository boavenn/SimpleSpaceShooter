#pragma once
#include "Weapon.hpp"

class QuadShot : public Weapon
{
public:
	QuadShot(Entity* entity);
	std::vector<Projectile*> getNewProjectiles(float v_mod) override;

private:
};