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
	bounceAmount(0),
	engine(eng)
{
	std::cout << "Create squareVisual" << "\n";
	squareVisual.setPosition(squarePos);
	squareVisual.setSize(sf::Vector2f(100, 100));
	squareVisual.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
	squareVisual.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
	
	LoadSprite("Assets/DvdLogoWhite.png");
}

// Update function
void Square::Update()
{
	// Square
	/*if (squarePos.x < 0 || squarePos.x > engine.screenSizeX - squareVisual.getSize().x)
	{
		velocity *= -1;
	}
	if (squarePos.y < 0 || squarePos.y > engine.screenSizeY - squareVisual.getSize().y)
	{
		velocity *= -1;
	}

	squarePos.x += velocity;
	squarePos.y += velocity;
	squareVisual.setPosition(squarePos);
	squareVisual.setPosition(squarePos);
	engine.window.draw(squareVisual);*/
	
	if (spritePosition.x < 0 || spritePosition.x > engine.screenSizeX - 200)
	{
		sprite.setColor(sf::Color(rand()% 256, rand() % 256, rand() % 256, 255));
		bounceAmount += 1;
		text.setString("Bounced: " + std::to_string(bounceAmount));
		velocityX *= -1;
	}
	if (spritePosition.y < 0 || spritePosition.y > engine.screenSizeY - 88)
	{
		sprite.setColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
		bounceAmount += 1;
		velocityY *= -1;
	}

	spritePosition = sprite.getPosition();
	spritePosition.x += velocityX;
	spritePosition.y += velocityY;
	sprite.setPosition(spritePosition);
	
	//std::cout << "Sprite X Position: " << spritePosition.x << "\n";
	//std::cout << "Sprite Y Position: " << spritePosition.x << "\n";

	engine.window.draw(sprite);
}

void Square::LoadSprite(std::string path)
{
	// Load DvdLogo Sprite
	texture.loadFromFile(path);
	sprite.setTexture(texture);

	int size = texture.getSize().x;
	int pixelSize = 200;
	float scale = (float)pixelSize / (float)size;
	sprite.setScale(scale, scale);

	sprite.setColor(sf::Color(255, 255, 255, 255));
}

// make the DisplayText in here tomorrow