#include "QuadShot.hpp"

QuadShot::QuadShot(Entity* entity) : Weapon(entity)
{
	base_dmg = 15.f;
}

std::vector<Projectile*> QuadShot::getNewProjectiles(float dmg_mod)
{
	float dmg = base_dmg * dmg_mod;
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile({ entity->top().x - 9.f, entity->top().y }, { -75.f, -300.f }, dmg, { 18, 0, 6, 16 }));
	temp.push_back(new Projectile({ entity->top().x - 3.f, entity->top().y }, { -25.f, -300.f }, dmg, { 18, 0, 6, 16 }));
	temp.push_back(new Projectile({ entity->top().x + 3.f, entity->top().y }, { 25.f, -300.f }, dmg, { 18, 0, 6, 16 }));
	temp.push_back(new Projectile({ entity->top().x + 9.f, entity->top().y }, { 75.f, -300.f }, dmg, { 18, 0, 6, 16 }));
	return temp;
}
