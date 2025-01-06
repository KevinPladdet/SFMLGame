#include "Square.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Square::Square()
{
	sf::RectangleShape square;
	sf::Vector2f squarePos(0, 0);
	square.setPosition(squarePos);
	square.setSize(sf::Vector2f(100, 100));
	square.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

	float velocityX = 3;
	float velocityY = 3;
}

void Square::Update()
{
	// Physics
	if (squarePos.x < 0 || squarePos.x > screenSizeX - square.getSize().x)
	{
		velocityX *= -1;
	}
	if (squarePos.y < 0 || squarePos.y > screenSizeY - square.getSize().y)
	{
		velocityY *= -1;
	}

	squarePos.x += velocityX;
	squarePos.y += velocityY;
	square.setPosition(squarePos);

	window.clear();
	window.draw(square);
	window.display();
}
