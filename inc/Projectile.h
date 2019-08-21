#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
class Projectile
{
public:
	Projectile(sf::IntRect rect, sf::Vector2f velocity, float dmg);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	const sf::Vector2f& getPosition() { return sprite.getPosition(); }
	const void setInitialPosition(sf::Vector2f pos) { sprite.setPosition(pos); }
	bool isOut();
private:
	sf::Sprite sprite;
	sf::Vector2f velocity;
	float angle;
	float damage;
};

