#include "..\inc\Explosion.h"

Explosion::Explosion(sf::Vector2f pos) : explosion(sf::IntRect(0, 0, 40, 40), 23, 0.02f, 0), particles(sf::PrimitiveType::Points, 100)
{
	sprite.setTexture(ResourceManager::get().textures.get("explosion"));
	sprite.setOrigin({ 20.f,20.f });
	sprite.setPosition(pos);
	sprite.setScale({ 2.f,2.f });
	
	particles_size = particles.getVertexCount();
	for (unsigned i = 0; i < particles_size; i++)
	{
		particles[i].color = sf::Color(255, rand() % 200, 0);
		particles[i].position = pos;
	}
}

void Explosion::update(float deltaTime)
{
	sprite.setTextureRect(explosion.update(deltaTime));
	updateParticles(deltaTime);
}

void Explosion::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
	w.draw(particles);
}

void Explosion::updateParticles(float deltaTime)
{
	// it's probably not very proffesional way to make a pseudo circle out of particles but I used x^2 + y^2 = r^2
	float modx = 0;
	float mody = 0;
	float r = 10.f;
	for (unsigned i = 0; i < particles_size; i++)
	{
		if (i <= 25)
		{
			mody = -sqrt(r * r - modx * modx);
			modx += r / 25.0f;
		}
		else if (i <= 50)
		{
			mody = sqrt(r * r - modx * modx);
			modx -= r / 25.0f;
		}
		else if (i <= 75)
		{
			mody = sqrt(r * r - modx * modx);
			modx -= r / 25.0f;
		}
		else if (i < 100)
		{
			mody = -sqrt(r * r - modx * modx);
			modx += r / 25.0f;
		}
		particles[i].position = { particles[i].position.x + float(rand() % 5 - 2) + modx / float(rand() % 50 + 100), particles[i].position.y + float(rand() % 5 - 2) + mody / float(rand() % 50 + 100) };
	}
}
