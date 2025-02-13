#include "Arrow.h"
#include "Engine/Engine.h"
#include "World.h"
#include <iostream>

Arrow::Arrow(Engine& eng, World& world)
	: engine(eng),
	world(world)
{
	LoadSprite("Assets/Arrow.png");
	CreateArrowBody();
}

void Arrow::LoadSprite(std::string path)
{
	texture.loadFromFile(path);
	arrowSprite.setTexture(texture);
}

void Arrow::CreateArrowBody()
{
	// Creating Arrow with Box2D
	b2BodyDef arrowDef = b2DefaultBodyDef();
	arrowDef.type = b2_dynamicBody;
	arrowDef.position = { 300.0f / world.worldScale, 200.0f / world.worldScale };
	arrowId = b2CreateBody(world.worldId, &arrowDef);
	b2Polygon arrowBox = b2MakeBox(0.5f, 0.125f);

	b2ShapeDef arrowShapeDef = b2DefaultShapeDef();
	arrowShapeDef.density = 1.0f;
	arrowShapeDef.friction = 0.3f;
	b2CreatePolygonShape(arrowId, &arrowShapeDef, &arrowBox);
}

void Arrow::Render()
{
	// Visualising Arrow
	b2Vec2 arrowPos = b2Body_GetPosition(arrowId);
	b2Rot arrowRot = b2Body_GetRotation(arrowId);
	
	float arrowAngle = std::atan2(arrowRot.s, arrowRot.c) * 180 / 3.14;

	sf::Vector2f arrowSize(1.0f * world.worldScale, 0.25f * world.worldScale);
	arrowSprite.setScale(arrowSize.x / texture.getSize().x, arrowSize.y / texture.getSize().y);
	arrowSprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	arrowSprite.setPosition(sf::Vector2f(arrowPos.x * world.worldScale, arrowPos.y * world.worldScale));
	arrowSprite.setRotation(arrowAngle);
	
	engine.window.draw(arrowSprite);
}