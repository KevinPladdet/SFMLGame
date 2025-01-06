#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Engine::Engine()
{
	
}

void Engine::Start()
{
	window.create(sf::VideoMode(screenSizeX, screenSizeY), "Insane game");
	window.setFramerateLimit(framerateLimit);
}

void Engine::LoopEngine()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			// Close window with escape key
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		// Render
		window.clear();
		window.display();
	}
}
