#pragma once
#include "box2d/box2d.h"
#include <SFML/Graphics.hpp>

class Engine;
class World
{
public:
	World(Engine& engine);
	void Update();
	void Render();
	void SpawnArrow(std::string path);

	// worldId is used to spawn body's in the world
	b2WorldId worldId;
	// worldScale is 50 because 50 pixels is 1 meter in Box2D
	const int worldScale = 50;

private:
	Engine& engine;

	// b2BodyId
	b2BodyId playerId;
	b2BodyId enemyId;
	b2BodyId platformLeftId;
	b2BodyId platformRightId;
	b2BodyId groundId;

	// Visualising shapes
	sf::RectangleShape player;
	sf::RectangleShape enemy;
	sf::RectangleShape platformLeft;
	sf::RectangleShape platformRight;
	sf::RectangleShape ground;
	
	float timeStep = 1.0f / 150.0f;
	int subStepCount = 4;

	// Moving Platform
	float leftPlatformSpeedY;
	float rightPlatformSpeedY;
	float minY;
	float maxY;

	// Arrow
	sf::Texture texture;
	sf::Sprite sprite;
};