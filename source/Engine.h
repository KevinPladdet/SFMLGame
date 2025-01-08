#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"

class Engine
{
public:
	Engine();
	void Start();
	void LoopEngine();

	sf::RenderWindow window;

	float screenSizeX = 800;
	float screenSizeY = 600;
private:
	float framerateLimit = 60;

	float spriteX = 0;
	float spriteY = 0;
	float spriteSpeed = 200;

	Engine& eng = *this;
	Square square;
};
