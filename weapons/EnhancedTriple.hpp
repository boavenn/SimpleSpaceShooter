#pragma once
#include "Weapon.hpp"

class EnhancedTriple : public Weapon
{
public:
	EnhancedTriple(Entity* entity);
	std::vector<Projectile*> getNewProjectiles(float dmg_mod) override;

private:
};