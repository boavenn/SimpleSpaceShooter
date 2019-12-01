#include "OneShot.hpp"
#include "../entities/Player.hpp"

OneShot::OneShot(Entity* entity) : Weapon(entity)
{
	base_dmg = 6.f;
}

std::vector<Projectile*> OneShot::getNewProjectiles(float dmg_mod)
{
	float dmg = base_dmg * dmg_mod;
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile(entity->top(), { 0.f, -300.f }, dmg, { 0, 0, 6, 16 }));
	return temp;
}
