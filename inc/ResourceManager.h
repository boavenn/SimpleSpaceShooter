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
		textures.add("explosion");
		textures.add("background"); textures.setTexRepeated("background");
		textures.add("layer1"); textures.setTexRepeated("layer1");
		textures.add("sidebar"); textures.setTexRepeated("sidebar");
		textures.add("pickups");
		buffers.add("blaster1");
		buffers.add("blaster2");
		buffers.add("blaster3");
		buffers.add("blaster4");
		buffers.add("explosion");
		buffers.add("shield");
		buffers.add("pickup");
		fonts.add("VCR_OSD_MONO_1.001");
	}

	ResourceHolder<sf::Texture> textures;
	ResourceHolder<sf::SoundBuffer> buffers;
	ResourceHolder<sf::Font> fonts;
private:
	ResourceManager() : textures("tex", "png"), buffers("audio", "wav"), fonts("fonts", "ttf") { init(); }
};

