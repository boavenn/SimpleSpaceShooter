#pragma once
#include "Pickup.hpp"
#include "../entities/Player.hpp"

class Speed : public Pickup
{
public:
	Speed(sf::Vector2f init_pos, sf::Vector2f velocity);
	void giveBonus(Player* player) override;
private:
};