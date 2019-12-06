#pragma once
#include "Pickup.hpp"
#include "../Player.hpp"

class BulletCapacity : public Pickup
{
public:
	BulletCapacity(sf::Vector2f init_pos, sf::Vector2f velocity);
	void giveBonus(Player* player) override;

private:
};