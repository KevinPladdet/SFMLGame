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
	squareVisual.setPosition(squarePos);
	squareVisual.setSize(sf::Vector2f(100, 100));
	squareVisual.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
	squareVisual.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
}

// Update function
void Square::Update()
{
	// Physics
	if (squarePos.x < 0 || squarePos.x > engine.screenSizeX - squareVisual.getSize().x)
	{
		velocityX *= -1;
	}
	if (squarePos.y < 0 || squarePos.y > engine.screenSizeY - squareVisual.getSize().y)
	{
		velocityY *= -1;
	}

	squarePos.x += velocityX;
	squarePos.y += velocityY;
	squareVisual.setPosition(squarePos);
	squareVisual.setPosition(squarePos);

	engine.window.draw(squareVisual);
	engine.window.draw(sprite);
}

void Square::LoadSprite(std::string path)
{
	sf::Texture texture;

	if (texture.loadFromFile(path))
	{
		std::cout << "Succesfully loaded " << path << "\n";
	}

	sprite.setTexture(texture);

	//sprite.setTexture(txr);

	// Resize sprite to pixelSize
	/*int size = texture.getSize().x;
	int pixelSize = 400;
	float scale = (float)pixelSize / (float)size;
	sprite.setScale(scale, scale);*/
}