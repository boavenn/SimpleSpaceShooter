#include "Alien03.hpp"

Alien03::Alien03(sf::Vector2f pos, int direction, float delay, float hp) : Alien(pos, hp, direction, delay)
{
	Animation* animation = new Animation(0.2f);
	for (int i = 0; i < 8; i++)
		animation->addFrame({ 50 * i, 100, 50, 50 });
	animations.insert(std::make_pair("Stationary", animation));

	animation = new Animation(0.1f, false);
	animation->addFrame({ 400, 100, 50, 50 });
	animations.insert(std::make_pair("GettingHit", animation));

	sprite.setTextureRect(animations.at("Stationary")->getFirstFrame());
	sprite.setOrigin({ 25.f, 25.f });
	sprite.setPosition(init_pos);

	addSoundBuffer("blaster1");

	dive_chance = 25;
	fire_chance = 20;
	score = 20;
}

void Alien03::update(float dt)
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

void Alien03::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}

std::vector<Projectile*> Alien03::getProjectiles()
{
	std::vector<Projectile*> temp;
	temp.push_back(new Projectile({ this->bottom().x - 8.f, this->bottom().y }, { 0.f, 425.f }, 1, { 16, 20, 8, 12 }));
	temp.push_back(new Projectile({ this->bottom().x + 8.f, this->bottom().y }, { 0.f, 425.f }, 1, { 16, 20, 8, 12 }));
	return temp;
}
