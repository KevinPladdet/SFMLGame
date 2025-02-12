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
	sf::RectangleShape playerVisual;
	sf::Vector2f playerInput;
	sf::Vector2f playerSize;
	float movementSpeed;
};