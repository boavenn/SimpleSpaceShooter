#include "DoubleShot.hpp"
#include "../entities/Player.hpp"

DoubleShot::DoubleShot(Entity* entity) : Weapon(entity)
{
	base_dmg = 11.f;
}

std::vector<Projectile*> DoubleShot::getNewProjectiles(float v_mod)
{
	float dmg = base_dmg;
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile({ entity->top().x - 10.f, entity->top().y }, { 0.f * v_mod, -350.f * v_mod }, dmg, { 10, 0, 8, 18 }));
	temp.push_back(new Projectile({ entity->top().x + 10.f, entity->top().y }, { 0.f * v_mod, -350.f * v_mod }, dmg, { 10, 0, 8, 18 }));
	return temp;
}
