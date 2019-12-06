#include "EnhancedTriple.hpp"

EnhancedTriple::EnhancedTriple(Entity* entity) : Weapon(entity)
{
	base_dmg = 16.f;
}

std::vector<Projectile*> EnhancedTriple::getNewProjectiles(float v_mod)
{
	float dmg = base_dmg;
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile({ entity->top().x - 10.f, entity->top().y }, { -100.f * v_mod, -450.f * v_mod }, dmg, { 40, 0, 12, 20 }));
	temp.push_back(new Projectile({ entity->top().x, entity->top().y }, { 0.f * v_mod, -450.f * v_mod }, dmg, { 40, 0, 12, 20 }));
	temp.push_back(new Projectile({ entity->top().x + 10.f, entity->top().y }, { 100.f * v_mod, -450.f * v_mod }, dmg, { 40, 0, 12, 20 }));
	return temp;
}
