#pragma once
#include "Pickup.hpp"
#include "../entities/Player.hpp"

class Money : public Pickup
{
public:
	Money(sf::Vector2f init_pos, sf::Vector2f velocity, int tier);
	void giveBonus(Player* player) override;
private:
	int value;
};