#include "Arrow.h"
#include "Engine/Engine.h"
#include "World.h"
#include "VolumeManager.h"
#include <iostream>

Arrow::Arrow(Engine& eng, World& world, VolumeManager& vm)
	: engine(eng),
	world(world),
	vm(vm)
{
	LoadSprite();
}

void Arrow::LoadSprite()
{
	arrowSprite.setTexture(world.arrowTexture);
}

void Arrow::CreateArrowBody()
{
	// Creating Arrow with Box2D
	b2BodyDef arrowDef = b2DefaultBodyDef();
	arrowDef.type = b2_dynamicBody;

	// Spawn Arrow inside of bow
	b2Vec2 spawnPos = {world.bowPos.x / world.worldScale, world.bowPos.y / world.worldScale };
	arrowDef.position = {spawnPos};

	arrowId = b2CreateBody(world.worldId, &arrowDef);
	b2Polygon arrowBox = b2MakeBox(0.5f, 0.125f);

	b2ShapeDef arrowShapeDef = b2DefaultShapeDef();
	arrowShapeDef.density = 1.0f;
	arrowShapeDef.friction = 0.3f;
	arrowShapeDef.enableHitEvents = true;
	arrowShapeDef.filter.categoryBits = LAYER_ARROW; // Set collision layer to LAYER_ARROW
	arrowShapeDef.filter.maskBits = 0xFFFF & ~LAYER_PLAYER; // Collide with every layer except LAYER_PLAYER
	b2CreatePolygonShape(arrowId, &arrowShapeDef, &arrowBox);

	float bowAngleRadians = world.bowRotation * (3.14 / 180);
	b2Body_SetTransform(arrowId, spawnPos, b2MakeRot(bowAngleRadians));
}

void Arrow::Render()
{
	// Visualising Arrow
	b2Vec2 arrowPos = b2Body_GetPosition(arrowId);
	b2Rot arrowRot = b2Body_GetRotation(arrowId);
	
	float arrowAngle = std::atan2(arrowRot.s, arrowRot.c) * 180 / 3.14;

	sf::Vector2f arrowSize(1.0f * world.worldScale, 0.25f * world.worldScale);
	arrowSprite.setScale(arrowSize.x / world.arrowTexture.getSize().x, arrowSize.y / world.arrowTexture.getSize().y);
	arrowSprite.setOrigin(world.arrowTexture.getSize().x / 2.0f, world.arrowTexture.getSize().y / 2.0f);
	arrowSprite.setPosition(sf::Vector2f(arrowPos.x * world.worldScale, arrowPos.y * world.worldScale));
	arrowSprite.setRotation(arrowAngle);
	
	engine.window.draw(arrowSprite);
}

void Arrow::DestroyArrow()
{
	b2DestroyBody(arrowId);
}

void Arrow::Update()
{
	// Apply small force to the front of the arrow
	b2Vec2 arrowVelocity = b2Body_GetLinearVelocity(arrowId);
	b2Vec2 arrowTip = b2Body_GetWorldPoint(arrowId, b2Vec2 {0.5f, 0.0f});
	b2Vec2 downwardsForce = b2Vec2{arrowVelocity.x * 0.07f, arrowVelocity.y * 0.07f};
	b2Body_ApplyForce(arrowId, downwardsForce, arrowTip, true);

	// Apply small drag force to the back of the arrow
	b2Vec2 arrowTail = b2Body_GetWorldPoint(arrowId, b2Vec2 {-0.5f, 0.0f});
	b2Vec2 dragForce = b2Vec2{-arrowVelocity.x * 0.02f, -arrowVelocity.y * 0.02f};
	b2Body_ApplyForce(arrowId, dragForce, arrowTail, true);
}

void Arrow::ArrowForce()
{
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(engine.window);
	sf::Vector2f mousePos = engine.window.mapPixelToCoords(mousePixelPos);

	sf::Vector2f distanceVector = mousePos - world.bowPos;
	float distance = std::sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);

	float bowAngleRadians = world.bowRotation * (3.14f / 180.0f);
	b2Vec2 forceDirection = {std::cos(bowAngleRadians), std::sin(bowAngleRadians)};

	float forceAmount = distance * 2.0f; // 2.0f is a magic number to increase force more
	forceDirection.x *= forceAmount;
	forceDirection.y *= forceAmount;
	
	b2Vec2 arrowPos = b2Body_GetPosition(arrowId);
	b2Body_ApplyForce(arrowId, forceDirection, arrowPos, true);
	vm.PlayArrowWhooshSFX();
}