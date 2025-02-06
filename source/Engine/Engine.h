#pragma once
#include <SFML/Graphics.hpp>
#include "Dvd.h" 
#include "Player.h"
#include "World.h"

class Engine
{
public:
	Engine();
	void Start();
	void LoopEngine();

	sf::RenderWindow window;
	
	float dt;

	float screenSizeX = 1280;
	float screenSizeY = 720;
private:
	Engine& eng = *this;
	unsigned int framerateLimit = 60;
	sf::Clock dt_clock;

	Dvd dvd;
	Player player;
	World world;
};