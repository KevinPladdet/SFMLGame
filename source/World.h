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

	// Visualising shapes
	sf::RectangleShape shape;
	sf::RectangleShape ground;

	// worldScale is 50 because 50 pixels is 1 meter in Box2D
	const int worldScale = 50;
	float timeStep = 1.0f / 150.0f;
	int subStepCount = 4;
};