#include "World.h"
#include "Engine/Engine.h"
#include <iostream>

World::World(Engine& eng)
	: engine(eng),
	leftVelocityY(5),
	rightVelocityY(5),
	minY(4.4),
	maxY(10)
{
	// Creating World
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, 10.0f };
	worldId = b2CreateWorld(&worldDef);

	// Creating PlayerLeft
	b2BodyDef playerLeftDef = b2DefaultBodyDef();
	playerLeftDef.type = b2_dynamicBody;
	playerLeftDef.position = { 265.0f / worldScale, 200.0f / worldScale };
	playerLeftId = b2CreateBody(worldId, &playerLeftDef);
	b2Polygon dynamicBoxLeft = b2MakeBox(0.5f, 0.5f);

	b2ShapeDef playerLeftShapeDef = b2DefaultShapeDef();
	playerLeftShapeDef.density = 1.0f;
	playerLeftShapeDef.friction = 0.3f;
	b2CreatePolygonShape(playerLeftId, &playerLeftShapeDef, &dynamicBoxLeft);

	// Creating PlayerRight
	b2BodyDef playerRightDef = b2DefaultBodyDef();
	playerRightDef.type = b2_dynamicBody;
	playerRightDef.position = { 1015.0f / worldScale, 200.0f / worldScale };
	playerRightId = b2CreateBody(worldId, &playerRightDef);
	b2Polygon dynamicBoxRight = b2MakeBox(0.5f, 0.5f);

	b2ShapeDef playerRightShapeDef = b2DefaultShapeDef();
	playerRightShapeDef.density = 1.0f;
	playerRightShapeDef.friction = 0.3f;
	b2CreatePolygonShape(playerRightId, &playerRightShapeDef, &dynamicBoxRight);

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
		leftVelocityY *= -1;
	}

	b2Vec2 velocityLeft = { 0.0f, leftVelocityY };
	b2Body_SetLinearVelocity(platformLeftId, velocityLeft);

	// Move platformRight
	b2Vec2 platformRightPosition = b2Body_GetPosition(platformRightId);

	if (platformRightPosition.y < minY || platformRightPosition.y > maxY)
	{
		rightVelocityY *= -1;
	}

	b2Vec2 velocityRight = { 0.0f, rightVelocityY };
	b2Body_SetLinearVelocity(platformRightId, velocityRight);
}

void World::Render(sf::RenderWindow& window)
{
	// Visualising playerLeft
	b2Vec2 playerLeftPos = b2Body_GetPosition(playerLeftId);
	b2Rot playerLeftRot = b2Body_GetRotation(playerLeftId);

	float playerLeftAngle = std::atan2(playerLeftRot.s, playerLeftRot.c) * 180 / 3.14;

	sf::Vector2f playerLeftSize(1.0f * worldScale, 1.0f * worldScale);
	playerLeft.setSize(playerLeftSize);
	playerLeft.setOrigin(playerLeftSize / 2.0f);
	playerLeft.setPosition(sf::Vector2f(playerLeftPos.x * worldScale, playerLeftPos.y * worldScale));
	playerLeft.setRotation(playerLeftAngle);
	engine.window.draw(playerLeft);

	// Visualising playerRight
	b2Vec2 playerRightPos = b2Body_GetPosition(playerRightId);
	b2Rot playerRightRot = b2Body_GetRotation(playerRightId);

	float playerRightAngle = std::atan2(playerRightRot.s, playerRightRot.c) * 180 / 3.14;

	sf::Vector2f playerRightSize(1.0f * worldScale, 1.0f * worldScale);
	playerRight.setSize(playerRightSize);
	playerRight.setOrigin(playerRightSize / 2.0f);
	playerRight.setPosition(sf::Vector2f(playerRightPos.x * worldScale, playerRightPos.y * worldScale));
	playerRight.setRotation(playerRightAngle);
	engine.window.draw(playerRight);

	// Visualizing platformLeft
	b2Vec2 platformLeftPosition = b2Body_GetPosition(platformLeftId);
	sf::Vector2f platformLeftSize(2.0f * worldScale, 0.5f * worldScale);
	platformLeft.setFillColor(sf::Color(255, 0, 0));
	platformLeft.setSize(platformLeftSize);
	platformLeft.setOrigin(platformLeftSize / 2.0f);
	platformLeft.setPosition(sf::Vector2f(platformLeftPosition.x * worldScale, platformLeftPosition.y * worldScale));
	engine.window.draw(platformLeft);

	// Visualizing platformRight
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