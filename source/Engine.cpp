#include "Engine.h"
#include "Square.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Engine::Engine()
	: square(*this)
{
	// Load DvdLogo Sprite
	/*sf::Texture txr;
	txr.loadFromFile("Assets/DvdLogo.png");
	sprite.setTexture(txr);
	square.LoadSprite(txr);*/
	
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
		square.Update();

		//window.draw(sprite);

		window.display();
	}
}
