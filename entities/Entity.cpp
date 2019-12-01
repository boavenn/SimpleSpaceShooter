#include "Entity.hpp"

bool Entity::contains(Entity* entity)
{
	sf::Vector2f pos = entity->getPosition();
	return (pos.x > this->left().x && pos.x < this->right().x && pos.y > this->top().y && pos.y < this->bottom().y);
}
