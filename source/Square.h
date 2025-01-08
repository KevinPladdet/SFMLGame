#pragma once
#include <SFML/Graphics.hpp>

class Engine;
class Square
{
public:
	Square(Engine& engine);
	void Update();
private:
	sf::RectangleShape square;
	sf::Vector2f squarePos;
	float velocityX;
	float velocityY;

	Engine& engine;
};