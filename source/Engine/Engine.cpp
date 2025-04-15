#include "Engine.h"
#include <SFML/Window.hpp>

Engine::Engine()
	: world(*this, volumeManager, clock),
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
	skyBackground.loadFromFile("Assets/SkyBackground.png");
	background.setTexture(skyBackground);
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
		}

		// Render
		window.clear();
		window.draw(background);
			
		world.Render();
		world.Update();
		
		if (world.activeMainMenu)
		{
			world.MainMenu();
		}

		window.display();
	}
}