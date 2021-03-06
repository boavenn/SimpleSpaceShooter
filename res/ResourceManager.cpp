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
	textures.add("sidebar");
	textures.add("player");
	textures.add("bullets");
	textures.add("aliens");
	textures.add("pickups");
	textures.add("buttons");
	textures.add("menubg");
	textures.add("util");
	textures.add("shop");
	for(int i = 1; i <=7; i++)
		textures.add("explosion" + std::to_string(i));

	audio.add("blaster1");
	audio.add("blaster2");
	audio.add("blaster3");
	audio.add("battle");
	audio.add("menu");
	audio.add("shop");
	audio.add("pickup");

	fonts.add("MonospaceTypewriter");
}
