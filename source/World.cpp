#include "World.h"
#include "Engine/Engine.h"
#include <iostream>

World::World(Engine& eng, Clock& clock)
	: engine(eng),
	clock(clock),
	minY(4.4),
	maxY(10),
	scoreAmount(-1), // -1 because it calls Reset() at the start, which does scoreAmount += 1
	limitedArrowsAmount(5),
	gameOver(true)
{
	arrowTexture.loadFromFile("Assets/Arrow.png");
	retryTexture.loadFromFile("Assets/RetryButton.png");
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seeds the rng so it's actually random each time
	leftPlatformSpeedY = (2 + std::rand() % 6);

	// Create scoreText
	font.loadFromFile("Assets/Fonts/VerdanaPro-CondRegular.ttf");
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setPosition(25, 0);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setString("Score: " + std::to_string(scoreAmount));

	// Create limitedArrowsSprite
	limitedArrowSprite.setTexture(arrowTexture);
	limitedArrowSprite.setScale(0.075, 0.075);
	limitedArrowSprite.setPosition(1205, 10);
	limitedArrowSprite.setRotation(45);

	// Create limitedArrowsText
	limitedArrowsText.setFont(font);
	limitedArrowsText.setCharacterSize(52);
	limitedArrowsText.setPosition(1160, 2);
	limitedArrowsText.setFillColor(sf::Color::Red);
	limitedArrowsText.setString(std::to_string(limitedArrowsAmount));

	#pragma region SetupGameOver
	// Create gameOverText
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(104);
	gameOverText.setPosition(370, 50);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("Game Over!");

	// Create retrySprite
	retrySprite.setTexture(retryTexture);
	retrySprite.setScale(0.5, 0.5);
	retrySprite.setPosition(370, 410);
	#pragma endregion SetupGameOver

	// Creating World
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, 25.0f };
	worldId = b2CreateWorld(&worldDef);

	// Creating Player
	b2BodyDef playerDef = b2DefaultBodyDef();
	playerDef.type = b2_kinematicBody;
	playerDef.position = { 200.0f / worldScale, 240.0f / worldScale };
	playerId = b2CreateBody(worldId, &playerDef);
	b2Polygon playerBox = b2MakeBox(0.5f, 1.0f);

	b2ShapeDef playerShapeDef = b2DefaultShapeDef();
	playerShapeDef.density = 1.0f;
	playerShapeDef.friction = 0.3f;
	b2CreatePolygonShape(playerId, &playerShapeDef, &playerBox);

	// Creating Enemy
	b2BodyDef enemyDef = b2DefaultBodyDef();
	enemyDef.type = b2_dynamicBody;
	enemyDef.position = { 1080.0f / worldScale, 350.0f / worldScale };
	enemyId = b2CreateBody(worldId, &enemyDef);
	b2Polygon enemyBox = b2MakeBox(0.5f, 1.0f);

	b2ShapeDef enemyShapeDef = b2DefaultShapeDef();
	enemyShapeDef.density = 1.0f;
	enemyShapeDef.friction = 0.3f;
	b2CreatePolygonShape(enemyId, &enemyShapeDef, &enemyBox);

	// Creating PlatformLeft
	b2BodyDef platformLeftBodyDef = b2DefaultBodyDef();
	platformLeftBodyDef.type = b2_kinematicBody;
	platformLeftBodyDef.position = { 200.0f / worldScale, 300.0f / worldScale };
	platformLeftId = b2CreateBody(worldId, &platformLeftBodyDef);
	
	b2Polygon platformLeftBox = b2MakeBox(1.0f, 0.25f);
	b2ShapeDef platformLeftShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(platformLeftId, &platformLeftShapeDef, &platformLeftBox);

	// Creating PlatformRight
	b2BodyDef platformRightBodyDef = b2DefaultBodyDef();
	platformRightBodyDef.type = b2_kinematicBody;
	platformRightBodyDef.position = { 1080.0f / worldScale, 400.0f / worldScale };
	platformRightId = b2CreateBody(worldId, &platformRightBodyDef);
	
	// Makes both platform move upwards upon running the game
	leftPlatformSpeedY *= -1;
	rightPlatformSpeedY *= -1;

	b2Polygon platformRightBox = b2MakeBox(1.0f, 0.25f);
	b2ShapeDef platformRightShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(platformRightId, &platformRightShapeDef, &platformRightBox);

	// Creating Ground
	b2BodyDef groundBodyDef = b2DefaultBodyDef();
	groundBodyDef.type = b2_kinematicBody;
	groundBodyDef.position = { 640.0f / worldScale, 710.0f / worldScale };
	groundId = b2CreateBody(worldId, &groundBodyDef);

	b2Polygon groundBox = b2MakeBox(12.8f, 0.25f);
	b2ShapeDef groundShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

	// Creating WallLeft
	b2BodyDef wallLeftBodyDef = b2DefaultBodyDef();
	wallLeftBodyDef.type = b2_kinematicBody;
	wallLeftBodyDef.position = { 10.0f / worldScale, 50.0f / worldScale };
	wallLeftId = b2CreateBody(worldId, &wallLeftBodyDef);

	b2Polygon wallLeftBox = b2MakeBox(0.25f, 14.4f);
	b2ShapeDef wallLeftShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(wallLeftId, &wallLeftShapeDef, &wallLeftBox);

	// Creating WallRight
	b2BodyDef wallRightBodyDef = b2DefaultBodyDef();
	wallRightBodyDef.type = b2_kinematicBody;
	wallRightBodyDef.position = { 1270.0f / worldScale, 50.0f / worldScale };
	wallRightId = b2CreateBody(worldId, &wallRightBodyDef);

	b2Polygon wallRightBox = b2MakeBox(0.25f, 14.4f);
	b2ShapeDef wallRightShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(wallRightId, &wallRightShapeDef, &wallRightBox);

	// Randomize Enemy position & PlatformRight position + speed
	Reset();
}

void World::Update()
{
	b2World_Step(worldId, timeStep, subStepCount);

	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(engine.window);
	sf::Vector2f mousePos = engine.window.mapPixelToCoords(mousePixelPos);
	
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
	
	// Applies the same velocity to the player as platformLeft
	#pragma region PlayerVelocity
	
	b2Vec2 playerVelocity = b2Body_GetLinearVelocity(playerId);
	playerVelocity.y = leftPlatformSpeedY;
	b2Body_SetLinearVelocity(playerId, playerVelocity);
	#pragma endregion PlayerVelocity

	// Enemy doesn't rotate / get launched up anymore unless hit by an arrow
	#pragma region EnemyVelocity
	b2Vec2 enemyPosition = b2Body_GetPosition(enemyId);

	// Floats for the platformRightTopY and enemyBottomY 
	// (will be used to calculate difference between them)
	float platformRightTopY = platformRightPosition.y - 0.25f;
	float enemyBottomY = enemyPosition.y - 1.0f;
	
	b2Rot enemyRot = b2Body_GetRotation(enemyId);
	float enemyAngle = std::atan2(enemyRot.s, enemyRot.c) * 180 / 3.14;

	// Checks if enemy is on the platform, if yes: apply the platform velocity to the enemy
	if (std::abs(enemyBottomY - platformRightTopY) < 2.02f) // Checks posY difference by 0.02
	{
		// Checks posX difference by 0.62f (0.5 is the amount to be halfway off the platform)
		if (std::abs(enemyPosition.x - platformRightPosition.x) < 0.62f)
		{
			// Checks if the enemy is rotating 
			// (otherwise it would still apply velocity after being hit by an arrow)
			if (std::abs(enemyAngle) < 0.5f)
			{
				// Applies the same velocity to the enemy as platformRight
				b2Vec2 enemyVelocity = b2Body_GetLinearVelocity(enemyId);
				enemyVelocity.y = rightPlatformSpeedY;
				b2Body_SetLinearVelocity(enemyId, enemyVelocity);
			}
		}
	}
	#pragma endregion EnemyVelocity

	// Detect Enemy Y position
	if (enemyPosition.y > 12.3f)
	{
		if (!waitForReset)
		{
			std::cout << "Started Reset Clock" << "\n";
			clock.StartTimer();
			waitForReset = true;
		}
	}
	else
	{
		waitForReset = false;
	}

	// Waits 3 seconds before calling Reset()
	if (clock.WaitForReset(3.0f) && waitForReset)
	{
		Reset();
	}

	// Wait 5 seconds before game over
	if (clock.WaitForGameOver(5.0f) && !waitForReset)
	{
		std::cout << "Game Over" << "\n";
		gameOver = true;
	}

	// Game Over
	if (gameOver)
	{
		engine.window.draw(gameOverText);
		engine.window.draw(retrySprite);

		if (mousePos.x >= 370 && mousePos.x <= 620 
			&& mousePos.y >= 410 && mousePos.y <= 560)
		{
			retrySprite.setColor(sf::Color::Green);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::cout << "Clicked Retry" << "\n";
				// TODO TOMORROW: MAKE IT SO IT ONLY DOES IT ONCE WHEN CLICKING
			}
		}
		else
		{
			retrySprite.setColor(sf::Color::Red);
		}
	}

	// Arrow Spawning
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		if (!keyPressedK && limitedArrowsAmount >= 1)
		{
			limitedArrowsAmount -= 1;
			limitedArrowsText.setString(std::to_string(limitedArrowsAmount));
			SpawnArrow();
			if (limitedArrowsAmount == 0)
			{
				std::cout << "Started Arrow Clock" << "\n";
				clock.StartTimer();
			}
			keyPressedK = true;
		}
	}
	else
	{
		keyPressedK = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if (!keyPressedR)
		{
			Reset();
			keyPressedR = true;
		}
	}
	else
	{
		keyPressedR = false;
	}

	engine.window.draw(scoreText);
	engine.window.draw(limitedArrowsText);
	engine.window.draw(limitedArrowSprite);
}

void World::Render()
{
	// Visualising Player
	b2Vec2 playerPos = b2Body_GetPosition(playerId);
	b2Rot playerRot = b2Body_GetRotation(playerId);

	float playerAngle = std::atan2(playerRot.s, playerRot.c) * 180 / 3.14;

	sf::Vector2f playerSize(1.0f * worldScale, 2.0f * worldScale);
	player.setSize(playerSize);
	player.setOrigin(playerSize / 2.0f);
	player.setPosition(sf::Vector2f(playerPos.x * worldScale, playerPos.y * worldScale));
	player.setRotation(playerAngle);
	engine.window.draw(player);

	// Visualising Enemy
	b2Vec2 enemyPos = b2Body_GetPosition(enemyId);
	b2Rot enemyRot = b2Body_GetRotation(enemyId);

	float enemyAngle = std::atan2(enemyRot.s, enemyRot.c) * 180 / 3.14;

	sf::Vector2f enemySize(1.0f * worldScale, 2.0 * worldScale);
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

	// Visualizing WallLeft
	b2Vec2 wallLeftPosition = b2Body_GetPosition(wallLeftId);
	sf::Vector2f wallLeftSize(0.5f * worldScale, 28.8f * worldScale);
	wallLeft.setFillColor(sf::Color(255, 0, 0));
	wallLeft.setSize(wallLeftSize);
	wallLeft.setOrigin(wallLeftSize / 2.0f);
	wallLeft.setPosition(sf::Vector2f(wallLeftPosition.x * worldScale, wallLeftPosition.y * worldScale));
	engine.window.draw(wallLeft);

	// Visualizing WallRight
	b2Vec2 wallRightPosition = b2Body_GetPosition(wallRightId);
	sf::Vector2f wallRightSize(0.5f * worldScale, 28.8f * worldScale);
	wallRight.setFillColor(sf::Color(255, 0, 0));
	wallRight.setSize(wallRightSize);
	wallRight.setOrigin(wallRightSize / 2.0f);
	wallRight.setPosition(sf::Vector2f(wallRightPosition.x * worldScale, wallRightPosition.y * worldScale));
	engine.window.draw(wallRight);
	
	for (auto& arrow : arrows)
	{
		arrow.Render();
		arrow.Update();
	}
}

void World::SpawnArrow()
{
	std::cout << "Spawned in Arrow" << std::endl;
	arrows.emplace_back(engine, *this, engine.volumeManager);
	arrows.back().CreateArrowBody();
	arrows.back().ArrowForce();
}

void World::DestroyArrows()
{
	for (auto& arrow : arrows)
	{
		arrow.DestroyArrow();
	}
	arrows.clear();
}

void World::Reset()
{
	std::cout << "Resetting" << "\n";

	// Destroy all Arrows
	DestroyArrows();

	// Increase Score
	scoreAmount += 1;
	scoreText.setString("Score: " + std::to_string(scoreAmount));

	// Reset limitedArrowsAmount
	limitedArrowsAmount = 5;
	limitedArrowsText.setString(std::to_string(limitedArrowsAmount));

	// Set random position and speed of platformRightId
	float randomX = 13.0f + static_cast<float>(std::rand()) / (RAND_MAX / (21.6f - 13.0f));
	float randomY = 4.4f + static_cast<float>(std::rand()) / (RAND_MAX / (10.0f - 4.4f));
	b2Body_SetTransform(platformRightId, { randomX, randomY }, b2MakeRot(0.0f));
	rightPlatformSpeedY = (2 + std::rand() % 10);
	
	// Platform will always spawn while moving upwards, never downwards
	rightPlatformSpeedY *= -1;

	// Position enemy above platform
	b2Body_SetTransform(enemyId, { randomX, randomY-1.2f }, b2MakeRot(0.0f));
}