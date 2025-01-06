#include "Time.h"

float Time::deltaTime = 0;
sf::Clock Time::clock;

void Time::UpdateTime()
{
	deltaTime = clock.restart().asSeconds();
}