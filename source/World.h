#pragma once
#include "box2d/box2d.h"
#include <SFML/Graphics.hpp>

class Engine;
class World
{
public:
	World(Engine& engine);
	void Update();
	void Render(sf::RenderWindow& window);

private:
	Engine& engine;

	b2WorldId worldId;
	b2BodyId groundId;
	b2BodyId bodyId;


	float timeStep = 1.0f / 200.0f;
	int subStepCount = 4;
};