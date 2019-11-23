#pragma once
#include "../res/ResourceManager.hpp"
#include "../util/Animation.hpp"
#include "Entity.hpp"

class Projectile : public Entity
{
public:
	Projectile(sf::Vector2f init_pos, sf::Vector2f velocity, float dmg, sf::IntRect rect);
	Projectile(sf::Vector2f init_pos, sf::Vector2f velocity, float dmg, Animation* animation);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& w) override;
	bool isOutOfMap();
	
private:
	Projectile(sf::Vector2f init_pos, sf::Vector2f velocity, float dmg);

	Animation* animation = nullptr;
	sf::IntRect rect;
	float angle;
	float damage;

// Getters
public:
	const float& getDamage() { return damage; }
	const sf::Vector2f& getVelocity() { return velocity; }
	const sf::IntRect& getRect() { return rect; }
};

