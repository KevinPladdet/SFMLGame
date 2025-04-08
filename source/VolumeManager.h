#pragma once
#include <SFML/Audio.hpp>

enum class SoundEffects
{
    Victory,
    GameOver,
    Retry,
};

class Engine;
class VolumeManager
{
public:
    VolumeManager(Engine& engine);
    void PlayArrowWhooshSFX();
    void PlaySFX(SoundEffects sfxName);

    
private:
    Engine& engine;

    std::vector<sf::Sound> arrowWhooshPool;
    sf::SoundBuffer arrowWhooshSFX;

    sf::SoundBuffer victorySFX;
    sf::Sound victorySound;

    sf::SoundBuffer gameoverSFX;
    sf::Sound gameoverSound;

    sf::SoundBuffer retrySFX;
    sf::Sound retrySound;
};