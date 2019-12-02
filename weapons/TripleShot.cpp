#include "TripleShot.hpp"

TripleShot::TripleShot(Entity* entity) : Weapon(entity)
{
	base_dmg = 10.f;
}

std::vector<Projectile*> TripleShot::getNewProjectiles(float dmg_mod)
{
	float dmg = base_dmg * dmg_mod;
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile({ entity->top().x - 10.f, entity->top().y }, { -100.f, -350.f }, dmg, { 20, 0, 8, 18 }));
	temp.push_back(new Projectile({ entity->top().x, entity->top().y }, { 0.f, -350.f }, dmg, { 20, 0, 8, 18 }));
	temp.push_back(new Projectile({ entity->top().x + 10.f, entity->top().y }, { 100.f, -350.f }, dmg, { 20, 0, 8, 18 }));
	return temp;
}
