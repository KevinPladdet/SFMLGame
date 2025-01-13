#pragma once
#include <SFML/Graphics.hpp>

class Engine;
class Player
{
public:
	Player(Engine& engine);
	void Update();
private:
	Engine& engine;

	// Player
	sf::RectangleShape player;
	sf::Vector2f playerPos;
	sf::Vector2f playerSize;
	const float movementSpeed;
};