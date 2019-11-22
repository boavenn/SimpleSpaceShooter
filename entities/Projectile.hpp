#pragma once
#include "../res/ResourceManager.hpp"
#include "../util/Animation.hpp"

class Projectile
{
public:
	Projectile(sf::Vector2f init_pos, sf::Vector2f velocity, float dmg, sf::IntRect rect);
	Projectile(sf::Vector2f init_pos, sf::Vector2f velocity, float dmg, Animation* animation);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	bool isOutOfMap();
	
private:
	Projectile(sf::Vector2f init_pos, sf::Vector2f velocity, float dmg);

	Animation* animation = nullptr;
	sf::Sprite sprite;
	sf::Vector2f velocity;
	sf::IntRect rect;
	float angle;
	float damage;

// Getters
public:
	const sf::Vector2f& getPosition() { return sprite.getPosition(); }
	const float& getDamage() { return damage; }
	const sf::Vector2f& getVelocity() { return velocity; }
	const sf::IntRect& getRect() { return rect; }
};

