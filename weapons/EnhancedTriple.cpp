#include "EnhancedTriple.hpp"

EnhancedTriple::EnhancedTriple(Entity* entity) : Weapon(entity)
{
	base_dmg = 20.f;
}

std::vector<Projectile*> EnhancedTriple::getNewProjectiles(float dmg_mod)
{
	float dmg = base_dmg * dmg_mod;
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile({ entity->top().x - 10.f, entity->top().y }, { -100.f, -450.f }, dmg, { 40, 0, 12, 20 }));
	temp.push_back(new Projectile({ entity->top().x, entity->top().y }, { 0.f, -450.f }, dmg, { 40, 0, 12, 20 }));
	temp.push_back(new Projectile({ entity->top().x + 10.f, entity->top().y }, { 100.f, -450.f }, dmg, { 40, 0, 12, 20 }));
	return temp;
}
