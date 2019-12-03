#include "ReloadTime.hpp"

ReloadTime::ReloadTime(sf::Vector2f init_pos, sf::Vector2f velocity) : Pickup(init_pos, velocity)
{
	animation = new Animation(0.1f);
	for (int i = 0; i < 12; i++)
		animation->addFrame({ 30 * i, 90, 30, 30 });

	sprite.setTextureRect(animation->getFirstFrame());
}

void ReloadTime::giveBonus(Player* player)
{
	if (!should_die)
	{
		player->decreaseReloadTime(0.005f);
		should_die = true;
	}
}
