#include "..\inc\Projectile.h"

Projectile::Projectile(sf::IntRect rect, sf::Vector2f velocity, float dmg, ProjType type)
{
	this->rect = rect;
	this->type = type;
	this->velocity = velocity;
	angle = (velocity.x / velocity.y) * (180.f / 3.14f); // we assume there wont be any horizontally moving projectiles
	damage = dmg;
	sprite.setTexture(ResourceManager::get().textures.get("bullets"));
	sprite.setTextureRect(rect);
	sprite.setOrigin({ float(rect.width / 2), float(rect.height / 2) });
	sprite.setRotation(-angle);
}

void Projectile::update(float deltaTime)
{
	sprite.move(velocity * deltaTime);
}

void Projectile::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}

bool Projectile::isOut()
{
	if (sprite.getPosition().y < -50.f || sprite.getPosition().y > 766.f)
		return true;
	return false;
}
