#pragma once
#include <SFML/Audio.hpp>

class Engine;
class VolumeManager
{
public:
    VolumeManager(Engine& engine);
    void PlayArrowWhooshSFX();

    sf::SoundBuffer arrowWhooshSFX;

    std::vector<sf::Sound> arrowWhooshPool;
private:
    Engine& engine;
};