#include "TripleShot.hpp"

TripleShot::TripleShot(Entity* entity) : Weapon(entity)
{

}

std::vector<Projectile*> TripleShot::getNewProjectiles()
{
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile({ entity->top().x - 10.f, entity->top().y }, { -100.f, -400.f }, 15.f, { 12, 0, 6, 16 }));
	temp.push_back(new Projectile({ entity->top().x, entity->top().y }, { 0.f, -400.f }, 15.f, { 12, 0, 6, 16 }));
	temp.push_back(new Projectile({ entity->top().x + 10.f, entity->top().y }, { 100.f, -400.f }, 15.f, { 12, 0, 6, 16 }));
	return temp;
}
