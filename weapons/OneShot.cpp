#include "OneShot.hpp"

OneShot::OneShot(Player* player) : Weapon(player)
{

}

std::vector<Projectile*> OneShot::getNewProjectiles()
{
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile(player->getTop(), { 0.f, -300.f }, 10.f, { 0, 0, 6, 16 }));
	return temp;
}
