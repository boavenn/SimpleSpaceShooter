#pragma once
#include "../Entity.hpp"
#include "../Projectile.hpp"
#include "../../res/ResourceManager.hpp"

class Alien : public Entity
{
public:
	Alien(float max_health);
	~Alien();
	bool gotHitBy(Projectile* proj);
	bool shouldDie() { return should_die; }

protected:
	std::unordered_map<std::string, Animation*> animations;
	float max_health;
	float current_health;
	bool got_hit = false;
	bool should_die = false;
};

