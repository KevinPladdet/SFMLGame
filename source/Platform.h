#pragma once
#include <SFML/Graphics.hpp>

class Engine;
class Platform
{
public:
	Platform(Engine& engine);
private:
	Engine& engine;

	// Platform
	sf::RectangleShape platformVisual;
	sf::Vector2f platformPos;
};