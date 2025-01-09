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

	float screenSizeX = 1280;
	float screenSizeY = 720;
private:
	unsigned int framerateLimit = 60;

	Engine& eng = *this;
	Square square;
	Platform platform;
};