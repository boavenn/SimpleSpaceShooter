#include "OneShot.hpp"
#include "../entities/Player.hpp"

OneShot::OneShot(Entity* entity) : Weapon(entity)
{

}

std::vector<Projectile*> OneShot::getNewProjectiles()
{
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile(entity->top(), { 0.f, -300.f }, 10.f, { 0, 0, 6, 16 }));
	return temp;
}
