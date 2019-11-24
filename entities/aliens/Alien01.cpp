#include "Alien01.hpp"

Alien01::Alien01(float max_health, sf::Vector2f pos) : Alien(max_health)
{
	Animation* animation = new Animation(0.2f);
	for (int i = 0; i < 8; i++)
		animation->addFrame({ 50 * i, 0, 50, 50 });
	animations.insert(std::make_pair("Stationary", animation));

	animation = new Animation(0.2f);
	animation->addFrame({ 400, 0, 50, 50 });
	animations.insert(std::make_pair("GettingHit", animation));

	sprite.setTextureRect(animations.at("Stationary")->getFirstFrame());
	sprite.setOrigin({ 25.f, 25.f });
	sprite.setPosition(pos);
}

void Alien01::update(float dt)
{
	if (got_hit)
	{
		Animation* gettingHitAnimation = animations.at("GettingHit");
		sprite.setTextureRect(gettingHitAnimation->update(dt));
		if (gettingHitAnimation->isAnimationEnded())
		{
			got_hit = false;
			gettingHitAnimation->resetAnimation();
			animations.at("Stationary")->resetAnimation();
		}
	}
	else
		sprite.setTextureRect(animations.at("Stationary")->update(dt));

	sprite.move(velocity * dt);
}

void Alien01::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}
