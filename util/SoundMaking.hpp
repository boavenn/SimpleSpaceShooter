#pragma once
#include <SFML/Audio.hpp>
#include "../res/ResourceManager.hpp"
#include <unordered_map>

class SoundMaking
{
public:
	SoundMaking(unsigned voices_size = 1);
	void playSound(std::string name, float pitch, float vol = 100.f, bool loop = false);
	void addSoundBuffer(std::string name);
	void stopAllSounds();
	void pauseAllSounds();
	void resumeAllSounds();

protected:
	std::unordered_map<std::string, sf::SoundBuffer> buffers;
	std::vector<sf::Sound> voices;
};