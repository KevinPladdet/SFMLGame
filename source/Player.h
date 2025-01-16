#pragma once
#include <SFML/Graphics.hpp>

class Engine;
class Platform;
class Player
{
public:
	Player(Engine& engine, Platform& platform);
	void Update();
private:
	Engine& engine;
	Platform& platform;

	// Player
	sf::RectangleShape playerVisual;
	sf::Vector2f playerInput;
	sf::Vector2f playerSize;
	const float movementSpeed;
};