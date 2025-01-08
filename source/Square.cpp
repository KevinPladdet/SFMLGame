#include "Square.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

// Start function
Square::Square(Engine& eng)
	: squarePos(0, 0),
	velocityX(3),
	velocityY(3),
	engine(eng)
{
	std::cout << "Create squareVisual" << "\n";
	sf::RectangleShape squareVisual;
	squareVisual.setPosition(squarePos);
	squareVisual.setSize(sf::Vector2f(100, 100));
	std::cout << "Set color" << "\n";
	squareVisual.setFillColor(sf::Color(255, 0, 0));
	std::cout << "Update" << "\n";
	Update();
}

// Update function
void Square::Update()
{
	//// Physics
	//if (squarePos.x < 0 || squarePos.x > engine.screenSizeX - square.getSize().x)
	//{
	//	velocityX *= -1;
	//}
	//if (squarePos.y < 0 || squarePos.y > engine.screenSizeY - square.getSize().y)
	//{
	//	velocityY *= -1;
	//}

	/*squarePos.x += velocityX;
	squarePos.y += velocityY;
	square.setPosition(squarePos);*/

	engine.window.draw(square);
}