#include "Alien01.hpp"

Alien01::Alien01(sf::Vector2f pos, int direction, float delay, float hp) : Alien(pos, hp, direction, delay)
{
	Animation* animation = new Animation(0.2f);
	for (int i = 0; i < 8; i++)
		animation->addFrame({ 50 * i, 0, 50, 50 });
	animations.insert(std::make_pair("Stationary", animation));

	animation = new Animation(0.1f, false);
	animation->addFrame({ 400, 0, 50, 50 });
	animations.insert(std::make_pair("GettingHit", animation));

	sprite.setTextureRect(animations.at("Stationary")->getFirstFrame());
	sprite.setOrigin({ 25.f, 25.f });
	sprite.setPosition(init_pos);

	addSoundBuffer("blaster1");

	dive_chance = 20;
	fire_chance = 15;
	score = 10;
}

void Alien01::update(float dt)
{
	if (!is_ascending)
	{
		firing = false;

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

		tryFire(dt);

		if (!in_berserk_mode)
		{
			checkDive(dt);
			if (is_diving)
				tryDive(dt);
		}
		else
			checkBerserkMode(dt);

		if (firing)
			playSound("blaster1", 1.f);

		sprite.move(velocity * dt);
	}
	else
		tryAscend(dt);
}

void Alien01::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}

std::vector<Projectile*> Alien01::getProjectiles()
{
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile(this->bottom(), { 0.f, 300.f }, 1, { 0, 20, 8, 12 }));
	return temp;
}
