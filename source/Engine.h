#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"

class Engine
{
public:
	Engine();
	void Start();
	void LoopEngine();
	void DisplayText();

	sf::RenderWindow window;

	float screenSizeX = 800;
	float screenSizeY = 600;
private:
	float framerateLimit = 60;


	Engine& eng = *this;
	Square square;
};
