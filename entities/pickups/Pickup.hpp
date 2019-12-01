#pragma once
#include "../Entity.hpp"
#include "../util/Animation.hpp"
#include "../util/WindowProperties.hpp"
#include "../res/ResourceManager.hpp"

class Player;

class Pickup : public Entity
{
public:
	Pickup(sf::Vector2f init_pos, sf::Vector2f velocity);
	void update(float dt);
	void draw(sf::RenderWindow& w);
	virtual void giveBonus(Player* player) = 0;
	bool shouldDie() { return should_die; }
	bool isOutOfMap() { return (sprite.getPosition().y < -50.f || sprite.getPosition().y > WindowProperties::getHeight()); }

protected:
	Animation* animation = nullptr;
	bool should_die = false;
};