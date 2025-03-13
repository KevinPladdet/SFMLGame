#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include "VolumeManager.h"
#include "Arrow.h"


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

	VolumeManager volumeManager;
private:
	Engine& eng = *this;
	unsigned int framerateLimit = 60;
	sf::Clock dt_clock;
	
	World world;
	Arrow arrow;
};