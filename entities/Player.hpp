#pragma once
#include <unordered_map>
#include "../util/Animation.hpp"
#include "../res/ResourceManager.hpp"

class Player
{
public:
	Player();
	~Player();
	void update(float dt);
	void draw(sf::RenderWindow& w);
	bool isFiring() { return is_firing; }

private:
	void checkInput();
	void checkAbilityToFire(float dt);
	void checkReload(float dt);

	std::unordered_map<std::string, Animation*> animations;
	sf::Sprite sprite;
	sf::Vector2f velocity = { 0, 0 };
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
	const sf::Vector2f& getPosition() { return sprite.getPosition(); }
	const sf::Vector2f& getTop() { return sf::Vector2f({ sprite.getPosition().x, sprite.getPosition().y - 35.f }); }
};

