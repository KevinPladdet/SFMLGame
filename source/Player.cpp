#include "Player.h"
#include "Engine.h"
#include "Platform.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player(Engine& eng, Platform& pform)
	: engine(eng),
	platform(pform),
	playerSize(50, 100),
	playerPos(0, 0),
	movementSpeed(100)
{
	playerVisual.setFillColor(sf::Color::Blue);
	playerVisual.setSize((playerSize, playerSize));
}

void Player::Update()
{
	playerPos.x = 0.f;
	playerPos.y = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		playerPos.y += -movementSpeed * engine.dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		playerPos.y += movementSpeed * engine.dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		playerPos.x += -movementSpeed * engine.dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		playerPos.x += movementSpeed * engine.dt;
	}

	playerVisual.move(playerPos);

	// Colliding with platformVisual
	if (playerVisual.getGlobalBounds().intersects(platform.platformVisual.getGlobalBounds()))
	{
		std::cout << "Colliding" << "\n";
	}

	engine.window.draw(playerVisual);
}