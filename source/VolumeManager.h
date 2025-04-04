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

    std::vector<sf::Sound> arrowWhooshPool;
private:
    Engine& engine;

    sf::SoundBuffer arrowWhooshSFX;

    sf::SoundBuffer victorySFX;
    sf::Sound victorySound;

    sf::SoundBuffer gameoverSFX;
    sf::Sound gameoverSound;

    sf::SoundBuffer retrySFX;
    sf::Sound retrySound;
};