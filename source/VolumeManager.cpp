#include "VolumeManager.h"
#include <iostream>

VolumeManager::VolumeManager(Engine& engine)
    : engine(engine)
{
	arrowWhooshSFX.loadFromFile("Assets/SFX/Whoosh.mp3");
	victorySFX.loadFromFile("Assets/SFX/VictorySFX.mp3");
	gameoverSFX.loadFromFile("Assets/SFX/GameOverSFX.mp3");
	retrySFX.loadFromFile("Assets/SFX/RetrySFX.mp3");

	for (int i = 0; i < 5; i++)
	{
		sf::Sound sound;
		sound.setBuffer(arrowWhooshSFX);
		arrowWhooshPool.push_back(sound);
	}

	victorySound.setBuffer(victorySFX);
	gameoverSound.setBuffer(gameoverSFX);
	retrySound.setBuffer(retrySFX);
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

void VolumeManager::PlaySFX(SoundEffects sfxName)
{
	switch (sfxName) 
	{
		case SoundEffects::Victory:
			victorySound.play();
			break;
		case SoundEffects::GameOver:
			gameoverSound.play();
			break;
		case SoundEffects::Retry:
			retrySound.play();
			break;
		default:
			break;
	}
}