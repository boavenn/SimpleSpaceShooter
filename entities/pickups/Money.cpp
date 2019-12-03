#include "Money.hpp"

Money::Money(sf::Vector2f init_pos, sf::Vector2f velocity, int tier) : Pickup(init_pos, velocity)
{
	animation = new Animation(0.1f);
	for (int i = 0; i < 12; i++)
		animation->addFrame({ 30 * i, 120 + 30 * tier, 30, 30 });

	sprite.setTextureRect(animation->getFirstFrame());

	switch (tier)
	{
	case 0:
		value = 10;
		break;
	case 1:
		value = 20;
		break;
	case 2:
		value = 50;
		break;
	case 3:
		value = 100;
		break;
	default:
		value = 0;
		break;
	}
}

void Money::giveBonus(Player* player)
{
	if (!should_die)
	{
		player->addMoney(value);
		should_die = true;
	}
}
