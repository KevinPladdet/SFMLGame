#include "Engine.h"
#include <SFML/Window.hpp>

Engine::Engine()
	: dvd(*this),
	player(*this),
	world(*this)
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
		dvd.Update();
		player.Update();

		world.Update();
		world.Render(window);

		window.display();
	}
}