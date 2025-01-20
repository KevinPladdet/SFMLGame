#include "World.h"
#include "Engine/Engine.h"
#include <iostream>

World::World(Engine& eng)
	: engine(eng)
{
	// Creating World
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, 10.0f };
	worldId = b2CreateWorld(&worldDef);

	// Creating Ground
	b2BodyDef groundBodyDef = b2DefaultBodyDef();
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position = { 3.0f, 500.0f / worldScale };
	groundId = b2CreateBody(worldId, &groundBodyDef);
	
	b2Polygon groundBox = b2MakeBox(0.5f, 0.5f);
	b2ShapeDef groundShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

	// Creating shape/body
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { 3.95f, 4.0f };
	bodyId = b2CreateBody(worldId, &bodyDef);

	b2Polygon dynamicBox = b2MakeBox(0.5f, 0.5f);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.3f;

	b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

void World::Update()
{
	b2World_Step(worldId, timeStep, subStepCount);
}

void World::Render(sf::RenderWindow& window)
{
	// Putting a RectangleShape on the shape/body
	b2Vec2 position = b2Body_GetPosition(bodyId);
	b2Rot rotation = b2Body_GetRotation(bodyId);

	float angle = std::atan2(rotation.s, rotation.c) * 180 / 3.14;
	std::cout << "Angle Radians: " << angle << "\n";

	sf::Vector2f shapeSize(1.0f * worldScale, 1.0f * worldScale);
	shape.setSize(shapeSize);
	shape.setOrigin(shapeSize / 2.0f);
	shape.setPosition(sf::Vector2f(position.x * worldScale, position.y * worldScale));
	shape.setRotation(angle);
	engine.window.draw(shape);

	// Putting a RectangleShape on the ground
	b2Vec2 groundPosition = b2Body_GetPosition(groundId);
	sf::Vector2f groundSize(1.0f * worldScale, 1.0f * worldScale);
	ground.setFillColor(sf::Color(255, 0, 0));
	ground.setSize(groundSize);
	ground.setOrigin(groundSize / 2.0f);
	ground.setPosition(sf::Vector2f(groundPosition.x * worldScale, groundPosition.y * worldScale));
	engine.window.draw(ground);
}