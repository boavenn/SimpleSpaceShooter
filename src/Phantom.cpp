#include "..\inc\Phantom.h"

void Phantom::play(int buffer_no, float pitch, float vol)
{
	for (auto& x : sound)
	{
		if (x.getStatus() == 0)
		{
			x.setBuffer(buffer[buffer_no]);
			x.setPitch(pitch);
			x.setVolume(vol);
			x.play();
			return;
		}
	}
}
