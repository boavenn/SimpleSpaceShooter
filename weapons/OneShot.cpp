#include "OneShot.hpp"
#include "../entities/Player.hpp"

OneShot::OneShot(Entity* entity) : Weapon(entity, "blaster2")
{
	base_dmg = 6.f;
}

std::vector<Projectile*> OneShot::getNewProjectiles(float v_mod)
{
	float dmg = base_dmg;
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile(entity->top(), { 0.f * v_mod, -350.f * v_mod }, dmg, { 0, 0, 8, 18 }));
	return temp;
}
