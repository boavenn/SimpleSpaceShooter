#include "Projectile.hpp"


Projectile::Projectile(sf::Vector2f init_pos, sf::Vector2f velocity, float dmg, sf::IntRect rect) : Projectile(init_pos, velocity, dmg)
{
	this->rect = rect;
	sprite.setTextureRect(rect);
	sprite.setOrigin({ float(rect.width / 2), float(rect.height / 2) });
}

Projectile::Projectile(sf::Vector2f init_pos, sf::Vector2f velocity, float dmg, Animation* animation) : Projectile(init_pos, velocity, dmg)
{
	this->animation = animation;
	sf::IntRect temp_rect = animation->getFirstFrame();
	sprite.setTextureRect(temp_rect);
	sprite.setOrigin({ float(temp_rect.width / 2), float(temp_rect.height / 2) });
}

Projectile::Projectile(sf::Vector2f init_pos, sf::Vector2f velocity, float dmg)
{
	this->velocity = velocity;
	damage = dmg;
	angle = atan2f(velocity.y, velocity.x) * (180.f / 3.14f);
	sprite.setTexture(ResourceManager::get().textures.get("bullets"));
	sprite.setPosition(init_pos);
	sprite.setRotation(angle + 90);
}

void Projectile::update(float deltaTime)
{
	sprite.move(velocity * deltaTime);
	if (animation != nullptr)
	{
		sprite.setTextureRect(animation->update(deltaTime));
	}
}

void Projectile::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}

bool Projectile::isOutOfMap()
{
	return (sprite.getPosition().y < -50.f || sprite.getPosition().x > 768.f);
}
