#pragma once
#include "Weapon.hpp"

class OneShot : public Weapon
{
public:
	OneShot(Player* player);
	std::vector<Projectile*> getNewProjectiles() override;

private:
};

