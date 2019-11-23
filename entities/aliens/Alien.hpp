#pragma once
#include "../Entity.hpp"
#include "../Projectile.hpp"
#include "../../res/ResourceManager.hpp"

class Alien : public Entity
{
public:
	Alien(float max_health);
	~Alien();
	virtual bool isHitBy(Projectile* proj) = 0;

protected:
	std::unordered_map<std::string, Animation*> animations;
	float max_health;
	float current_health;
};

