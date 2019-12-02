#include "DoubleShot.hpp"
#include "../entities/Player.hpp"

DoubleShot::DoubleShot(Entity* entity) : Weapon(entity)
{
	base_dmg = 5.f;
}

std::vector<Projectile*> DoubleShot::getNewProjectiles(float dmg_mod)
{
	float dmg = base_dmg * dmg_mod;
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile({ entity->top().x - 10.f, entity->top().y }, { 0.f, -700.f }, dmg, { 10, 0, 8, 18 }));
	temp.push_back(new Projectile({ entity->top().x + 10.f, entity->top().y }, { 0.f, -700.f }, dmg, { 10, 0, 8, 18 }));
	return temp;
}
