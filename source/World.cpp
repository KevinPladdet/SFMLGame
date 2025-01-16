#include "World.h"
#include "Engine/Engine.h"
#include <iostream>

World::World(Engine& eng)
	: engine(eng)
{
	std::cout << "Creating World" << "\n";

	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, 10.0f };
	worldId = b2CreateWorld(&worldDef);

	b2BodyDef groundBodyDef = b2DefaultBodyDef();
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position = { 0.0f, 720.0f / 50 };
	groundId = b2CreateBody(worldId, &groundBodyDef);

	b2Polygon groundBox = b2MakeBox(50.0f, 1.0f);
	b2ShapeDef groundShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { 0.5f, 4.0f };
	bodyId = b2CreateBody(worldId, &bodyDef);

	b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.3f;

	b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

void World::Update()
{
	b2World_Step(worldId, timeStep, subStepCount);
	//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, b2Rot_GetAngle(rotation));
	//engine.window.draw(bodyId);
}

void World::Render(sf::RenderWindow& window)
{
	sf::RectangleShape shape;
	const int worldScale = 50;
	b2Vec2 position = b2Body_GetPosition(bodyId);
	b2Rot rotation = b2Body_GetRotation(bodyId);
	shape.setSize(sf::Vector2f(50, 50));
	shape.setOrigin(sf::Vector2f(25, 25));
	shape.setPosition(sf::Vector2f(position.x * worldScale, position.y * worldScale));
	std::cout << "Y Position: " << position.y * 50 << "\n";
	engine.window.draw(shape);
}