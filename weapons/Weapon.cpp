#include "Weapon.hpp"

Weapon::Weapon(Entity* entity, std::string sound)
{
	this->sound = sound;
	this->entity = entity;
}
