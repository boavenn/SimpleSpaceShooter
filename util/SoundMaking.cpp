#include "SoundMaking.hpp"

SoundMaking::SoundMaking(unsigned voices_size) : voices(voices_size)
{

}

void SoundMaking::playSound(std::string name, float pitch, float vol)
{
	for (auto& v : voices)
	{
		if (v.getStatus() == sf::Sound::Stopped)
		{
			v.setBuffer(buffers.at(name));
			v.setPitch(pitch);
			v.setVolume(vol);
			v.play();
			return;
		}
	}

	// we add a new voice to the vector when there is no more voices available

	voices.push_back(sf::Sound());
	voices.back().setBuffer(buffers.at(name));
	voices.back().setPitch(pitch);
	voices.back().setVolume(vol);
	voices.back().play();
}

void SoundMaking::addSoundBuffer(std::string name)
{
	buffers.insert(std::make_pair(name, ResourceManager::get().audio.get(name)));
}

void SoundMaking::stopAllSounds()
{
	for (auto& v : voices)
	{
		if (v.getStatus() == sf::Sound::Playing)
		{
			v.stop();
		}
	}
}

void SoundMaking::pauseAllSounds()
{
	for (auto& v : voices)
	{
		if (v.getStatus() == sf::Sound::Playing)
		{
			v.pause();
		}
	}
}

void SoundMaking::resumeAllSounds()
{
	for (auto& v : voices)
	{
		if (v.getStatus() == sf::Sound::Paused)
		{
			v.play();
		}
	}
}
