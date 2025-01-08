#include "Engine.h"
#include "Square.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Engine::Engine()
	: square(*this)
{
	
	// Load DvdLogo Sprite
	/*texture.loadFromFile("Assets/DvdLogo.png");
	sprite.setTexture(texture);

	int size = texture.getSize().x;
	int pixelSize = 400;
	float scale = (float)pixelSize / (float)size;
	sprite.setScale(scale, scale);*/

	/*LoadSprite("Assets/DvdLogo.png");*/
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

//void Engine::LoadSprite(std::string path)
//{
//	// Load DvdLogo Sprite
//	texture.loadFromFile(path);
//	sprite.setTexture(texture);
//
//	int size = texture.getSize().x;
//	int pixelSize = 400;
//	float scale = (float)pixelSize / (float)size;
//	sprite.setScale(scale, scale);
//}