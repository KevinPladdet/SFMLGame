#pragma once
#include "box2d/box2d.h"
#include <SFML/Graphics.hpp>
#include "Arrow.h"

class Engine;
class Clock;
class World
{
public:
	World(Engine& engine, Clock& clock);
	void Update();
	void Render();
	void SpawnArrow();
	void DestroyArrows();
	void Reset();

	// worldId is used to spawn body's in the world
	b2WorldId worldId;
	b2BodyId playerId;

	// worldScale is 50 because 50 pixels is 1 meter in Box2D
	const int worldScale = 50;

	// Arrow Texture
	sf::Texture arrowTexture;

private:
	Engine& engine;
	Clock& clock;

	std::vector<Arrow> arrows;
	
	bool keyPressedK;
	bool keyPressedR;
	bool clockRunning;

	// b2BodyId
	b2BodyId enemyId;

	b2BodyId platformLeftId;
	b2BodyId platformRightId;

	b2BodyId groundId;
	b2BodyId wallLeftId;
	b2BodyId wallRightId;


	// Visualising shapes
	sf::RectangleShape player;
	sf::RectangleShape enemy;

	sf::RectangleShape platformLeft;
	sf::RectangleShape platformRight;

	sf::RectangleShape ground;
	sf::RectangleShape wallLeft;
	sf::RectangleShape wallRight;
	
	// World values
	float timeStep = 1.0f / 150.0f;
	int subStepCount = 4;

	// Moving Platform
	float leftPlatformSpeedY;
	float rightPlatformSpeedY;
	float minY;
	float maxY;

	// Score Text
	sf::Font font;
	sf::Text scoreText;
	int scoreAmount;
};