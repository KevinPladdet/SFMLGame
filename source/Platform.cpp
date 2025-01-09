#include "Platform.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Platform::Platform(Engine& eng)
	: platformPos(0, 0),
	engine(eng)
{
	std::cout << "Create Platform" << "\n";
	platformVisual.setPosition(platformPos);
	platformVisual.setSize(sf::Vector2f(100, 100));
}