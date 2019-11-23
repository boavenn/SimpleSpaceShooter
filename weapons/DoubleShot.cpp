#include "DoubleShot.hpp"
#include "../entities/Player.hpp"

DoubleShot::DoubleShot(Player* player) : Weapon(player)
{

}

std::vector<Projectile*> DoubleShot::getNewProjectiles()
{
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile({ player->getTop().x - 10.f, player->getTop().y }, { 0.f, -300.f }, 1.f, { 6, 0, 6, 16 }));
	temp.push_back(new Projectile({ player->getTop().x + 10.f, player->getTop().y }, { 0.f, -300.f }, 1.f, { 6, 0, 6, 16 }));
	return temp;
}
