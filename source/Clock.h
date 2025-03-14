#pragma once
#include <SFML/System.hpp>
#include <chrono>

class Engine;
class Clock
{
public:
    Clock(Engine& engine);
    void StartTimer();
    bool WaitForSeconds(float duration);
        
private:
    Engine& engine;
    
    sf::Clock clock;
    bool running;
};