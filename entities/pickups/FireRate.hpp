#pragma once
#include "Pickup.hpp"
#include "../Player.hpp"

class FireRate : public Pickup
{
public:
	FireRate(sf::Vector2f init_pos, sf::Vector2f velocity);
	void giveBonus(Player* player) override;

private:
};