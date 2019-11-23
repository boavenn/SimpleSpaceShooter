#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& w) = 0;

protected:
	sf::Sprite sprite;
	sf::Vector2f velocity = { 0, 0 };

public:
	sf::Vector2f getPosition() { return sprite.getPosition(); }
};

