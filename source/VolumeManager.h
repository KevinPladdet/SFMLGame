#pragma once
#include <SFML/Audio.hpp>

class Engine;
class VolumeManager
{
public:
    VolumeManager(Engine& engine);

    sf::SoundBuffer buffer;
    sf::Sound arrowWhooshSFX;
private:
    Engine& engine;
};