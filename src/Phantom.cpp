#include "..\inc\Phantom.h"

void Phantom::play(std::string name, float pitch, float vol)
{
	for (auto& x : sound)
	{
		if (x.getStatus() == 0)
		{
			x.setBuffer(buffer.at(name));
			x.setPitch(pitch);
			x.setVolume(vol);
			x.play();
			return;
		}
	}
}

bool Phantom::isHit(std::vector<Projectile>& projectiles)
{
	float half_width = sprite.getLocalBounds().width / 2.f;
	float half_height = sprite.getLocalBounds().height / 2.f;
	for (unsigned i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].getPosition().x >= sprite.getPosition().x - half_width && projectiles[i].getPosition().x <= sprite.getPosition().x + half_width &&
			projectiles[i].getPosition().y >= sprite.getPosition().y - half_height && projectiles[i].getPosition().y <= sprite.getPosition().y + half_height)
		{
			gotHit = true;
			currHealth -= projectiles[i].getDmg();
			projectiles.erase(projectiles.begin() + i);
			if (currHealth <= 0)
				died = true;
			return true;
		}
	}
	return false;
}
