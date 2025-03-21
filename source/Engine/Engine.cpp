#include "Engine.h"
#include <SFML/Window.hpp>

Engine::Engine()
	: world(*this, clock),
	volumeManager(*this),
	clock(*this),
	arrow(*this, world, volumeManager)
{
	Start();
}

void Engine::Start()
{
	window.create(sf::VideoMode(screenSizeX, screenSizeY), "Insane game");
	window.setFramerateLimit(framerateLimit);
	LoopEngine();
}

void Engine::LoopEngine()
{
	while (window.isOpen())
	{
		dt = dt_clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		// Render
		window.clear();

		world.Update();
		world.Render();

		window.display();
	}
}