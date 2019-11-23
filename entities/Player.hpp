#pragma once
#include <unordered_map>
#include "../util/Animation.hpp"
#include "../res/ResourceManager.hpp"
#include "../util/WindowProperties.hpp"
#include "../weapons/OneShot.hpp"
#include "../weapons/DoubleShot.hpp"
#include "Entity.hpp"


class Player : public Entity
{
public:
	Player();
	~Player();
	void update(float dt) override;
	void draw(sf::RenderWindow& w) override;
	bool isFiring() { return is_firing; }

private:
	void checkInput();
	void checkAbilityToFire(float dt);
	void checkReload(float dt);

	std::unordered_map<std::string, Animation*> animations;
	std::vector<Weapon*> weapons;
	int active_weapon = 1;
	bool try_fire = false;
	bool is_firing = false;
	float shot_gap = 0.3f;
	float shot_timer = 0.f;
	float reload_time = 0.5f;
	float reload_timer = 0.f;
	int bullets_capacity = 5;
	int bullets_ready = 5;

// Getter and Setters
public:
	sf::Vector2f getTop() { return sf::Vector2f({ sprite.getPosition().x, sprite.getPosition().y - 35.f }); }
	std::vector<Projectile*> getNewWeaponProjectiles() { return weapons[active_weapon]->getNewProjectiles(); }
	void setWeapon(Weapon* weapon) { this->weapons[active_weapon] = weapon; }
};

