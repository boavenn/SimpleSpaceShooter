#pragma once
#include "Weapon.hpp"
#include "../entities/Player.hpp"

class OneShot : public Weapon
{
public:
	OneShot(Player* player);
	std::vector<Projectile*> getNewProjectiles() override;

private:
};

