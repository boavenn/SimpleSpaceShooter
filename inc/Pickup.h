#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "ResourceManager.h"

class Pickup
{
public:
	enum PickupType
	{
		speedInc = 1
	};

public:
	Pickup(sf::Vector2f pos);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	const sf::Vector2f& getPosition() { return sprite.getPosition(); };
	const PickupType& getType() { return type; };
	bool isOut() { return (getPosition().y > 800.f) ? true : false; };

private:
	sf::IntRect setRect(PickupType type);

	sf::Sprite sprite;
	sf::Vector2f velocity = { 0, 150.f };
	Random rand;
	PickupType type;

};

