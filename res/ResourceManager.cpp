#include "ResourceManager.hpp"

ResourceManager& ResourceManager::get()
{
	static ResourceManager r;
	return r;
}

ResourceManager::ResourceManager() : textures("tex", "png"), audio("audio", "wav"), fonts("fonts", "ttf")
{
	// Here the loading of resources is done
	textures.add("background"); textures.get("background").setRepeated(true);
	textures.add("layer1"); textures.get("layer1").setRepeated(true);
	textures.add("player");
	textures.add("bullets");
	textures.add("aliens");
	textures.add("pickups");
	for(int i = 1; i <=4; i++)
		textures.add("explosion" + std::to_string(i));
	audio.add("explosion1");
	audio.add("blaster1");
	audio.add("blaster3");
	fonts.add("VCR_OSD_MONO_1.001");
}
