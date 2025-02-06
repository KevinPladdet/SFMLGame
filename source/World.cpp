#include "World.h"
#include "Engine/Engine.h"
#include <iostream>

World::World(Engine& eng)
	: engine(eng),
	minY(4.4),
	maxY(10)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seeds the rng so it's actually random each time
	leftPlatformSpeedY = (2 + std::rand() % 6),
	rightPlatformSpeedY = (2 + std::rand() % 6),
	std::cout << "leftPlatformSpeedY: " << leftPlatformSpeedY << "\n";
	std::cout << "rightPlatformSpeedY: " << rightPlatformSpeedY << "\n";
	// Creating World
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, 25.0f };
	worldId = b2CreateWorld(&worldDef);

	// Creating Player
	b2BodyDef playerDef = b2DefaultBodyDef();
	playerDef.type = b2_dynamicBody;
	playerDef.position = { 265.0f / worldScale, 200.0f / worldScale };
	playerId = b2CreateBody(worldId, &playerDef);
	b2Polygon playerBox = b2MakeBox(0.5f, 0.5f);

	b2ShapeDef playerShapeDef = b2DefaultShapeDef();
	playerShapeDef.density = 1.0f;
	playerShapeDef.friction = 0.3f;
	b2CreatePolygonShape(playerId, &playerShapeDef, &playerBox);

	// Creating Enemy
	b2BodyDef enemyDef = b2DefaultBodyDef();
	enemyDef.type = b2_dynamicBody;
	enemyDef.position = { 1015.0f / worldScale, 200.0f / worldScale };
	enemyId = b2CreateBody(worldId, &enemyDef);
	b2Polygon enemyBox = b2MakeBox(0.5f, 0.5f);

	b2ShapeDef enemyShapeDef = b2DefaultShapeDef();
	enemyShapeDef.density = 1.0f;
	enemyShapeDef.friction = 0.3f;
	b2CreatePolygonShape(enemyId, &enemyShapeDef, &enemyBox);

	// Creating PlatformLeft
	b2BodyDef platformLeftBodyDef = b2DefaultBodyDef();
	platformLeftBodyDef.type = b2_kinematicBody;
	platformLeftBodyDef.position = { 200.0f / worldScale, 400.0f / worldScale };
	platformLeftId = b2CreateBody(worldId, &platformLeftBodyDef);
	
	b2Polygon platformLeftBox = b2MakeBox(1.0f, 0.25f);
	b2ShapeDef platformLeftShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(platformLeftId, &platformLeftShapeDef, &platformLeftBox);

	// Creating PlatformRight
	b2BodyDef platformRightBodyDef = b2DefaultBodyDef();
	platformRightBodyDef.type = b2_kinematicBody;
	platformRightBodyDef.position = { 1080.0f / worldScale, 400.0f / worldScale };
	platformRightId = b2CreateBody(worldId, &platformRightBodyDef);

	b2Polygon platformRightBox = b2MakeBox(1.0f, 0.25f);
	b2ShapeDef platformRightShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(platformRightId, &platformRightShapeDef, &platformRightBox);

	// Creating Ground
	b2BodyDef groundBodyDef = b2DefaultBodyDef();
	groundBodyDef.type = b2_kinematicBody;
	groundBodyDef.position = { 640.0f / worldScale, 710.0f / worldScale };
	groundId = b2CreateBody(worldId, &groundBodyDef);

	b2Polygon groundBox = b2MakeBox(25.6f, 0.25f);
	b2ShapeDef groundShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);
}

void World::Update()
{
	b2World_Step(worldId, timeStep, subStepCount);
	
	// Move platformLeft
	b2Vec2 platformLeftPosition = b2Body_GetPosition(platformLeftId);

	if (platformLeftPosition.y < minY || platformLeftPosition.y > maxY)
	{
		leftPlatformSpeedY *= -1;
	}

	b2Vec2 velocityLeft = { 0.0f, leftPlatformSpeedY };
	b2Body_SetLinearVelocity(platformLeftId, velocityLeft);

	// Move platformRight
	b2Vec2 platformRightPosition = b2Body_GetPosition(platformRightId);

	if (platformRightPosition.y < minY || platformRightPosition.y > maxY)
	{
		rightPlatformSpeedY *= -1;
	}

	b2Vec2 velocityRight = { 0.0f, rightPlatformSpeedY };
	b2Body_SetLinearVelocity(platformRightId, velocityRight);
}

void World::Render(sf::RenderWindow& window)
{
	// Visualising Player
	b2Vec2 playerPos = b2Body_GetPosition(playerId);
	b2Rot playerRot = b2Body_GetRotation(playerId);

	float playerAngle = std::atan2(playerRot.s, playerRot.c) * 180 / 3.14;

	sf::Vector2f playerSize(1.0f * worldScale, 1.0f * worldScale);
	player.setSize(playerSize);
	player.setOrigin(playerSize / 2.0f);
	player.setPosition(sf::Vector2f(playerPos.x * worldScale, playerPos.y * worldScale));
	player.setRotation(playerAngle);
	engine.window.draw(player);

	// Visualising Enemy
	b2Vec2 enemyPos = b2Body_GetPosition(enemyId);
	b2Rot enemyRot = b2Body_GetRotation(enemyId);

	float enemyAngle = std::atan2(enemyRot.s, enemyRot.c) * 180 / 3.14;

	sf::Vector2f enemySize(1.0f * worldScale, 1.0f * worldScale);
	enemy.setSize(enemySize);
	enemy.setOrigin(enemySize / 2.0f);
	enemy.setPosition(sf::Vector2f(enemyPos.x * worldScale, enemyPos.y * worldScale));
	enemy.setRotation(enemyAngle);
	engine.window.draw(enemy);

	// Visualizing PlatformLeft
	b2Vec2 platformLeftPosition = b2Body_GetPosition(platformLeftId);
	sf::Vector2f platformLeftSize(2.0f * worldScale, 0.5f * worldScale);
	platformLeft.setFillColor(sf::Color(255, 0, 0));
	platformLeft.setSize(platformLeftSize);
	platformLeft.setOrigin(platformLeftSize / 2.0f);
	platformLeft.setPosition(sf::Vector2f(platformLeftPosition.x * worldScale, platformLeftPosition.y * worldScale));
	engine.window.draw(platformLeft);

	// Visualizing PlatformRight
	b2Vec2 platformRightPosition = b2Body_GetPosition(platformRightId);
	sf::Vector2f platformRightSize(2.0f * worldScale, 0.5f * worldScale);
	platformRight.setFillColor(sf::Color(255, 0, 0));
	platformRight.setSize(platformRightSize);
	platformRight.setOrigin(platformRightSize / 2.0f);
	platformRight.setPosition(sf::Vector2f(platformRightPosition.x * worldScale, platformRightPosition.y * worldScale));
	engine.window.draw(platformRight);

	// Visualizing Ground
	b2Vec2 groundPosition = b2Body_GetPosition(groundId);
	sf::Vector2f groundSize(25.6f * worldScale, 0.5f * worldScale);
	ground.setFillColor(sf::Color(255, 0, 0));
	ground.setSize(groundSize);
	ground.setOrigin(groundSize / 2.0f);
	ground.setPosition(sf::Vector2f(groundPosition.x * worldScale, groundPosition.y * worldScale));
	engine.window.draw(ground);
}