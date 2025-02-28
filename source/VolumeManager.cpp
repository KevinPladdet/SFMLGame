#include "VolumeManager.h"
#include <iostream>

VolumeManager::VolumeManager(Engine& engine)
    : engine(engine)
{
	// Arrow Whoosh SFX
	if (!buffer.loadFromFile("Assets/SFX/Whoosh.mp3"))
	{
		std::cout << "ERROR: Whoosh.mp3 didn't load correctly" << "\n";
	}
    arrowWhooshSFX.setBuffer(buffer);

	// Hit SFX

	// Victory SFX
}