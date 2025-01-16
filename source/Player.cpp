#include "Player.h"
#include "Engine.h"
#include "Platform.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player(Engine& eng, Platform& pform)
	: engine(eng),
	platform(pform),
	playerSize(50, 100),
	playerInput(0, 0),
	movementSpeed(300)
{
	playerVisual.setFillColor(sf::Color::Blue);
	playerVisual.setSize((playerSize, playerSize));
}

void Player::Update()
{
	playerInput.x = 0.f;
	playerInput.y = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		playerInput.y += -movementSpeed * engine.dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		playerInput.y += movementSpeed * engine.dt;
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		playerInput.x += -movementSpeed * engine.dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		playerInput.x += movementSpeed * engine.dt;
	}
	
	playerVisual.move(playerInput);

	// Colliding with Screen Edges
	// Top Edge Collision
	if (playerVisual.getPosition().y < 0.f)
	{
		playerVisual.setPosition(playerVisual.getPosition().x, 0.f);
	}
	// Bottom Edge Collision
	if (playerVisual.getPosition().y + playerVisual.getGlobalBounds().height > engine.screenSizeY)
	{
		playerVisual.setPosition(playerVisual.getPosition().x, engine.screenSizeY - playerVisual.getGlobalBounds().height);
	}
	// Left Edge Collision
	if (playerVisual.getPosition().x < 0.f) 
	{
		playerVisual.setPosition(0.f, playerVisual.getPosition().y);
	}
	// Right Edge Collision
	if (playerVisual.getPosition().x + playerVisual.getGlobalBounds().width > engine.screenSizeX)
	{
		playerVisual.setPosition(engine.screenSizeX - playerVisual.getGlobalBounds().width, playerVisual.getPosition().y);
	}

	// Colliding with Platform
	if (playerVisual.getGlobalBounds().intersects(platform.platformVisual.getGlobalBounds()))
	{
		std::cout << "Colliding" << "\n";
		movementSpeed = 0;
	}
	else
	{
		movementSpeed = 100;
	}

	engine.window.draw(playerVisual);
}