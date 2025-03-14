#include "Clock.h"
#include <iostream>

Clock::Clock(Engine& engine)
	: engine(engine),
    running(false)
{

}

void Clock::StartTimer()
{
    clock.restart();
    running = true;
}

// Checks if clock passed duration
bool Clock::WaitForSeconds(float duration)
{
    if (running && clock.getElapsedTime().asSeconds() >= duration)
    {
        running = false;
        return true;
    }
    return false;
}