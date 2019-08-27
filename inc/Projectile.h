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
	const sf::Vector2f& getPosition() const { return sprite.getPosition(); }
	void setInitialPosition(sf::Vector2f pos) { sprite.setPosition(pos); }
	float getDmg() const { return damage; }
	sf::Vector2f getVelocity() { return velocity; };
	sf::IntRect getRect() { return rect; };
	ProjType getType() { return type; };
	bool isOut();

private:
	sf::Sprite sprite;
	sf::Vector2f velocity;
	sf::IntRect rect;
	float angle;
	float damage;
	ProjType type;
};

