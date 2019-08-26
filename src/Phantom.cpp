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
