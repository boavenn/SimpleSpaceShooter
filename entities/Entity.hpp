#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& w) = 0;
	float left() { return sprite.getGlobalBounds().left; }
	float top() { return sprite.getGlobalBounds().top; }
	float right() { return sprite.getGlobalBounds().left + sprite.getGlobalBounds().width; }
	float bottom() { return sprite.getGlobalBounds().top + sprite.getGlobalBounds().height; }

protected:
	sf::Sprite sprite;
	sf::Vector2f velocity = { 0, 0 };

public:
	sf::Vector2f getPosition() { return sprite.getPosition(); }
};

