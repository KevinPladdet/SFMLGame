#include "Dvd.h"
#include "Engine/Engine.h"
#include <iostream>

// Start function
Dvd::Dvd(Engine& eng)
	: velocityX(3),
	velocityY(3),
	bounceAmount(0),
	engine(eng)
{	
	LoadSprite("Assets/DvdLogoWhite.png");
	DisplayText();
}

// Update function
void Dvd::Update()
{	
	if (spritePosition.x < 0 || spritePosition.x > engine.screenSizeX - 200)
	{
		sprite.setColor(sf::Color(rand()% 256, rand() % 256, rand() % 256, 255));
		velocityX *= -1;
		bounceAmount += 1;
		text.setString("Bounced: " + std::to_string(bounceAmount));
	}
	if (spritePosition.y < 0 || spritePosition.y > engine.screenSizeY - 113)
	{
		sprite.setColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
		velocityY *= -1;
		bounceAmount += 1;
		text.setString("Bounced: " + std::to_string(bounceAmount));
	}

	spritePosition = sprite.getPosition();
	spritePosition.x += velocityX;
	spritePosition.y += velocityY;
	sprite.setPosition(spritePosition);

	engine.window.draw(sprite);
	engine.window.draw(text);
}

void Dvd::LoadSprite(std::string path)
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

void Dvd::DisplayText()
{
	font.loadFromFile("Assets/Fonts/VerdanaPro-CondRegular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setString("Bounced: " + std::to_string(bounceAmount));
}