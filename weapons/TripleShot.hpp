#pragma once
#include "Weapon.hpp"

class TripleShot : public Weapon
{
public:
	TripleShot(Entity* entity);
	std::vector<Projectile*> getNewProjectiles() override;

private:
};