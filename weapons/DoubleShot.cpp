#include "DoubleShot.hpp"
#include "../entities/Player.hpp"

DoubleShot::DoubleShot(Entity* entity) : Weapon(entity)
{

}

std::vector<Projectile*> DoubleShot::getNewProjectiles()
{
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile({ entity->top().x - 10.f, entity->top().y }, { 0.f, -600.f }, 20.f, { 6, 0, 6, 16 }));
	temp.push_back(new Projectile({ entity->top().x + 10.f, entity->top().y }, { 0.f, -600.f }, 20.f, { 6, 0, 6, 16 }));
	return temp;
}
