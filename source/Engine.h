#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include "Platform.h"

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
	unsigned int framerateLimit = 60;

	Engine& eng = *this;
	Square square;
	Platform platform;
};