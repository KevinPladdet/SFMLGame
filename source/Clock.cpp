#include "Clock.h"
#include <iostream>

Clock::Clock(Engine& engine)
	: engine(engine),
    running1(false),
    running2(false)
{

}

void Clock::StartClock()
{
    clock.restart();
    running1 = true;
    running2 = true;
}

void Clock::StopClock()
{
    running1 = false;
    running2 = false;
}

// Checks if clock passed duration, if yes it will call Reset() in World.cpp
bool Clock::WaitForReset(float duration)
{
    if (running1 && clock.getElapsedTime().asSeconds() >= duration)
    {
        running1 = false;
        return true;
    }
    return false;
}

// Checks if clock passed duration, if yes it will enable the game over menu
bool Clock::WaitForGameOver(float duration)
{
    if (running2 && clock.getElapsedTime().asSeconds() >= duration)
    {
        running2 = false;
        return true;
    }
    return false;
}