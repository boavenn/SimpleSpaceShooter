#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& w) = 0;
	sf::Vector2f left() { return { sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2 }; }
	sf::Vector2f top() { return { sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().top }; }
	sf::Vector2f right() { return { sprite.getGlobalBounds().left + sprite.getGlobalBounds().width, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2 }; }
	sf::Vector2f bottom() { return { sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height }; }

protected:
	sf::Sprite sprite;
	sf::Vector2f velocity = { 0, 0 };

public:
	sf::Vector2f getPosition() { return sprite.getPosition(); }
};

