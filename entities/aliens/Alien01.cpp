#include "Alien01.hpp"

Alien01::Alien01(float max_health, sf::Vector2f pos) : Alien(max_health)
{
	Animation* animation = new Animation(0.2f);
	for (int i = 0; i < 8; i++)
		animation->addFrame({ 50 * i, 0, 50, 50 });
	animations.insert(std::make_pair("Stationary", animation));

	sprite.setTextureRect(animations.at("Stationary")->getFirstFrame());
	sprite.setOrigin({ 25.f, 25.f });
	sprite.setPosition(pos);
}

void Alien01::update(float dt)
{
	sprite.setTextureRect(animations.at("Stationary")->update(dt));
}

void Alien01::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}

bool Alien01::isHitBy(Projectile* proj)
{
	return false;
}
