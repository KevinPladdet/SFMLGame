#include "Engine.h"
#include "Square.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

Engine::Engine()
	: square(*this)
{
	Start();
}

void Engine::Start()
{
	window.create(sf::VideoMode(screenSizeX, screenSizeY), "Insane game");
	window.setFramerateLimit(framerateLimit);

	DisplayText();

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		// Render
		window.clear();
		square.Update();
		
		window.draw(text);

		window.display();
	}
}

//void Engine::DisplayText()
//{
//	
//	if (square.font.loadFromFile("Assets/Fonts/VerdanaPro-CondRegular.ttf"))
//	{
//		std::cout << "Font loaded succesfully" << "\n";
//	}
//	text.setFont(font);
//	text.setCharacterSize(24);
//	text.setFillColor(sf::Color::Red);
//	text.setString("Bounced: " + std::to_string(square.bounceAmount));
//}