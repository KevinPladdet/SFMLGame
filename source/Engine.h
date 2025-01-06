#pragma once
class Engine
{
public:
	Engine();
	void Start();
	void LoopEngine();
private:
	sf::RenderWindow window;

	float screenSizeX = 800;
	float screenSizeY = 600;

	float framerateLimit = 60;

	float spriteX = 0;
	float spriteY = 0;
	float spriteSpeed = 200;
};
