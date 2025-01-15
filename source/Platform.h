#pragma once
#include <SFML/Graphics.hpp>

class Engine;
class Platform
{
public:
	Platform(Engine& engine);
	void Update();

	sf::RectangleShape platformVisual;
private:
	Engine& engine;

	// Platform
	sf::Vector2f platformPos;
	float velocityY;
};