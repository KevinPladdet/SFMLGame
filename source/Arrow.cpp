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

	// Spawn Arrow next to Player
	b2Vec2 playerPos = b2Body_GetPosition(world.playerId);
	b2Vec2 spawnPos = {playerPos.x + 1.0f, playerPos.y};
	arrowDef.position = {spawnPos};

	arrowId = b2CreateBody(world.worldId, &arrowDef);
	b2Polygon arrowBox = b2MakeBox(0.5f, 0.125f);

	b2ShapeDef arrowShapeDef = b2DefaultShapeDef();
	arrowShapeDef.density = 1.0f;
	arrowShapeDef.friction = 0.3f;
	b2CreatePolygonShape(arrowId, &arrowShapeDef, &arrowBox);

	// Rotate Arrow to mousePos
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(engine.window);
	sf::Vector2f mousePos = engine.window.mapPixelToCoords(mousePixelPos);
	
	sf::Vector2f arrowSpawnPos(spawnPos.x * world.worldScale, spawnPos.y * world.worldScale);
	sf::Vector2f direction = mousePos - arrowSpawnPos;
	float angleRad = std::atan2(direction.y, direction.x);

	b2Body_SetTransform(arrowId, spawnPos, b2MakeRot(angleRad));
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		if (!keyPressed)
		{
			std::cout << "Applying force" << "\n";
			ArrowForce();
			keyPressed = true;
		}
	}
	else
	{
		keyPressed = false;
	}

	// Apply small force to the front of the arrow
	b2Vec2 arrowVelocity = b2Body_GetLinearVelocity(arrowId);
	b2Vec2 arrowTip = b2Body_GetWorldPoint(arrowId, b2Vec2{ 0.5f, 0.0f });
	b2Vec2 downwardsForce = b2Vec2{ arrowVelocity.x * 0.07f, arrowVelocity.y * 0.07f };
	b2Body_ApplyForce(arrowId, downwardsForce, arrowTip, true);
}

void Arrow::ArrowForce()
{
	// Get mousePos
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(engine.window);
	sf::Vector2f mousePos = engine.window.mapPixelToCoords(mousePixelPos);

	// Get arrowPos
	b2Vec2 arrowPixelPos = b2Body_GetPosition(arrowId);
	sf::Vector2f arrowPos(arrowPixelPos.x * world.worldScale, arrowPixelPos.y * world.worldScale);

	// Get direction and distance of the arrow
	sf::Vector2f arrowDirection = mousePos - arrowPos;

	std::cout << "Play SFX" << "\n";
	vm.arrowWhooshSFX.play();

	b2Vec2 forceDirection{ arrowDirection.x * 100.0f / world.worldScale, arrowDirection.y * 100.0f / world.worldScale };

	b2Body_ApplyForce(arrowId, forceDirection, arrowPixelPos, true);
}