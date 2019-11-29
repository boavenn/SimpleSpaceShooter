#pragma once
#include <unordered_map>
#include "../util/Animation.hpp"
#include "../res/ResourceManager.hpp"
#include "../util/WindowProperties.hpp"
#include "../weapons/OneShot.hpp"
#include "../weapons/DoubleShot.hpp"
#include "../weapons/TripleShot.hpp"
#include "../weapons/QuadShot.hpp"
#include "../util/SoundMaking.hpp"
#include "Entity.hpp"


class Player : public Entity, public SoundMaking
{
public:
	Player();
	~Player();
	void update(float dt) override;
	void draw(sf::RenderWindow& w) override;
	bool gotHitBy(Projectile* proj);
	bool isFiring() { return is_firing; }
	bool isImmune() { return is_immune || is_immune_on_death; }
	bool shouldExplode() { return should_explode; }
	bool lostAllLives() { return lost_all_lives; }

private:
	void checkInput();
	void checkAbilityToFire(float dt);
	void checkReload(float dt);
	void checkImmunity(float dt);
	void checkInputBlock(float dt);

	std::unordered_map<std::string, Animation*> animations;
	std::vector<Weapon*> weapons;

	// util
	bool try_fire = false;
	bool is_firing = false;
	bool block_input = false;
	bool should_explode = false;
	float on_death_input_block_time = 1.f;
	float input_block_timer = 0.f;
	bool lost_all_lives = false;
	float shot_timer = 0.f;
	float reload_timer = 0.f;
	int bullets_ready = 5;
	bool is_immune = false;
	bool is_immune_on_death = false;
	float immunity_timer = 0.f;
	float on_death_immunity_time = 3.f;

	// stats
	int active_weapon = 2;
	int bullets_capacity = 5;
	float reload_time = 0.5f;
	float shot_gap = 0.1f;
	int lives_max = 3;
	int lives_left = 2;
	float speed = 300.f;
	int money = 0;

// Stats manipulation
public:
	void addLive();
	void subLive();
	void addSpeed(float speed);
	void addMoney(int amount);
	void setImmunity();

// Getter and Setters
public:
	std::vector<Projectile*> getNewWeaponProjectiles() { return weapons[active_weapon]->getNewProjectiles(); }
	void setWeapon(Weapon* weapon) { this->weapons[active_weapon] = weapon; }
};

