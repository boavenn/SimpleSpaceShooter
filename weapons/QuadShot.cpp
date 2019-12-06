#include "QuadShot.hpp"

QuadShot::QuadShot(Entity* entity) : Weapon(entity)
{
	base_dmg = 15.f;
}

std::vector<Projectile*> QuadShot::getNewProjectiles(float v_mod)
{
	float dmg = base_dmg;
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile({ entity->top().x - 9.f, entity->top().y }, { -75.f * v_mod, -350.f * v_mod }, dmg, { 30, 0, 8, 18 }));
	temp.push_back(new Projectile({ entity->top().x - 3.f, entity->top().y }, { -25.f * v_mod, -350.f * v_mod }, dmg, { 30, 0, 8, 18 }));
	temp.push_back(new Projectile({ entity->top().x + 3.f, entity->top().y }, { 25.f * v_mod, -350.f * v_mod }, dmg, { 30, 0, 8, 18 }));
	temp.push_back(new Projectile({ entity->top().x + 9.f, entity->top().y }, { 75.f * v_mod, -350.f * v_mod }, dmg, { 30, 0, 8, 18 }));
	return temp;
}
