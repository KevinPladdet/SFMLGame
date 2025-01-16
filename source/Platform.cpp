#include "Platform.h"
#include "Engine/Engine.h"
#include <iostream>

Platform::Platform(Engine& eng)
	: platformPos(200, 400),
	velocityY(1),
	engine(eng)
{
	std::cout << "Create Platform" << "\n";
	platformVisual.setPosition(platformPos);
	platformVisual.setSize(sf::Vector2f(100, 25));
	platformVisual.setFillColor(sf::Color(255, 0, 0));
}

void Platform::Update()
{
	if (platformPos.y < 200 || platformPos.y > engine.screenSizeY - 220)
	{
		velocityY *= -1;
	}

	platformPos.y += velocityY;
	platformVisual.setPosition(platformPos);
	engine.window.draw(platformVisual);
}