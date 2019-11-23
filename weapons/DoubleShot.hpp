#pragma once
#include "Weapon.hpp"

class DoubleShot : public Weapon
{
public:
	DoubleShot(Player* player);
	std::vector<Projectile*> getNewProjectiles() override;

private:
};

