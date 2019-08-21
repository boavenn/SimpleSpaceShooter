#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourceHolder.h"
class ResourceManager
{
public:
	static ResourceManager& get() { static ResourceManager manager; return manager; }
	void init() // we load all needed resources down here
	{
		textures.add("player");
		textures.add("bullets");
		textures.add("enemies");
		buffers.add("blaster1");
	}

	ResourceHolder<sf::Texture> textures;
	ResourceHolder<sf::SoundBuffer> buffers;
private:
	ResourceManager() : textures("tex", "png"), buffers("audio", "wav") { init(); }
};

