#include "Player.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player(Engine& eng)
	: engine(eng),
	playerSize(50, 100),
	playerPos(0, 0),
	movementSpeed(100)
{
	player.setFillColor(sf::Color::Blue);
	player.setSize((playerSize, playerSize));
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

	player.move(playerPos);

	engine.window.draw(player);
}