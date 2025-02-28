#include "VolumeManager.h"
#include <iostream>

VolumeManager::VolumeManager(Engine& engine)
    : engine(engine)
{
	// Arrow Whoosh SFX
	if (!arrowWhooshSFX.loadFromFile("Assets/SFX/Whoosh.mp3"))
	{
		std::cout << "ERROR: Whoosh.mp3 didn't load correctly" << "\n";
	}

	for (int i = 0; i < 5; i++)
	{
		sf::Sound sound;
		sound.setBuffer(arrowWhooshSFX);
		arrowWhooshPool.push_back(sound);
	}

	// Hit SFX

	// Victory SFX
}

void VolumeManager::PlayArrowWhooshSFX()
{
	for (auto& sound : arrowWhooshPool)
	{
		if (sound.getStatus() != sf::Sound::Playing)
		{
			sound.play();
			return;
		}
	}
}