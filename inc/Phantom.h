#pragma once
#include "ResourceManager.h"
#include "Animation.h"
#include "Projectile.h"
#include <unordered_map>

class Phantom
{
public:
	Phantom(unsigned max_sounds) : sound(max_sounds) {}
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& w) { w.draw(sprite); }
	virtual void play(std::string name, float pitch, float vol = 100.f);
	virtual const sf::Vector2f& getPosition() const { return sprite.getPosition(); }
	virtual bool isShooting() const { return try_shoot; }
	virtual bool isHit(std::vector<Projectile>& projectiles);

	bool died = false;
protected:
	sf::Sprite sprite;
	sf::Vector2f velocity;
	std::unordered_map<std::string, sf::SoundBuffer> buffer;
	std::vector<sf::Sound> sound;
	bool try_shoot = false;
	bool gotHit = false;
	float currHealth = 0.f;
	unsigned lives = 1;
};

