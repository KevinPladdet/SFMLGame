#include "World.h"
#include "Engine/Engine.h"
#include <iostream>

World::World(Engine& eng)
	: engine(eng),
	velocityY(5),
	minY(4.4),
	maxY(10)
{
	// Creating World
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, 10.0f };
	worldId = b2CreateWorld(&worldDef);

	// Creating PlatformOne
	b2BodyDef groundBodyDef = b2DefaultBodyDef();
	groundBodyDef.type = b2_kinematicBody;
	groundBodyDef.position = { 4.0f, 400.0f / worldScale };
	platformOneId = b2CreateBody(worldId, &groundBodyDef);
	
	b2Polygon groundBox = b2MakeBox(1.0f, 0.25f);
	b2ShapeDef groundShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(platformOneId, &groundShapeDef, &groundBox);

	// Creating PlayerOne
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { 3.95f, 4.0f };
	playerOneId = b2CreateBody(worldId, &bodyDef);

	b2Polygon dynamicBox = b2MakeBox(0.5f, 0.5f);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.3f;
	b2CreatePolygonShape(playerOneId, &shapeDef, &dynamicBox);
}

void World::Update()
{
	b2World_Step(worldId, timeStep, subStepCount);
	
	// Move left platform
	b2Vec2 groundPosition = b2Body_GetPosition(platformOneId);
	std::cout << "PlatformOne Position: (" << groundPosition.x << ", " << groundPosition.y << ")\n";

	if (groundPosition.y < minY || groundPosition.y > maxY)
	{
		velocityY *= -1;
	}

	b2Vec2 velocity = { 0.0f, velocityY };
	b2Body_SetLinearVelocity(platformOneId, velocity);
}

void World::Render(sf::RenderWindow& window)
{
	// Putting a RectangleShape on the shape/body
	b2Vec2 position = b2Body_GetPosition(playerOneId);
	b2Rot rotation = b2Body_GetRotation(playerOneId);

	float angle = std::atan2(rotation.s, rotation.c) * 180 / 3.14;
	//std::cout << "Angle Radians: " << angle << "\n";

	sf::Vector2f shapeSize(1.0f * worldScale, 1.0f * worldScale);
	playerOne.setSize(shapeSize);
	playerOne.setOrigin(shapeSize / 2.0f);
	playerOne.setPosition(sf::Vector2f(position.x * worldScale, position.y * worldScale));
	playerOne.setRotation(angle);
	engine.window.draw(playerOne);

	// Putting a RectangleShape on the ground
	b2Vec2 groundPosition = b2Body_GetPosition(platformOneId);
	sf::Vector2f groundSize(2.0f * worldScale, 0.5f * worldScale);
	platformOne.setFillColor(sf::Color(255, 0, 0));
	platformOne.setSize(groundSize);
	platformOne.setOrigin(groundSize / 2.0f);
	platformOne.setPosition(sf::Vector2f(groundPosition.x * worldScale, groundPosition.y * worldScale));
	engine.window.draw(platformOne);
}