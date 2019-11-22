#include "ResourceManager.hpp"

ResourceManager& ResourceManager::get()
{
	static ResourceManager r;
	return r;
}

ResourceManager::ResourceManager() : textures("tex", "png"), audio("audio", "wav"), fonts("fonts", "ttf")
{
	// Here the loading of resources is done
	textures.add("background");
	textures.add("player");
}
