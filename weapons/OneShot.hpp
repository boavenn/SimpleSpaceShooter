#pragma once
#include "Weapon.hpp"

class OneShot : public Weapon
{
public:
	OneShot(Entity* entity);
	std::vector<Projectile*> getNewProjectiles() override;

private:
};

