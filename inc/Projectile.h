#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Projectile
{
public:
	enum ProjType
	{
		normal = 1,
		chaining
	};

public:
	Projectile(sf::IntRect rect, sf::Vector2f velocity, float dmg, ProjType type = normal);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	void setInitialPosition(sf::Vector2f pos) { sprite.setPosition(pos); }
	bool isOut();
	const sf::Vector2f& getPosition() { return sprite.getPosition(); }
	const float& getDmg() { return damage; }
	const sf::Vector2f& getVelocity() { return velocity; };
	const sf::IntRect& getRect() { return rect; };
	const ProjType& getType() { return type; };

private:
	sf::Sprite sprite;
	sf::Vector2f velocity;
	sf::IntRect rect;
	float angle;
	float damage;
	ProjType type;
};

