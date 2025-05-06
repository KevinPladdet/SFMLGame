#include "World.h"
#include "Engine/Engine.h"
#include <iostream>

World::World(Engine& eng, VolumeManager& vm, Clock& clock)
	: engine(eng),
	vm(vm),
	clock(clock),
	minY(4.4),
	maxY(10),
	scoreAmount(0),
	highscoreAmount(0),
	limitedArrowsAmount(5),
	gameOver(false),
	activePauseMenu(false),
	activeMainMenu(true),
	canActivateMenu(true),
	resetKeyEnabled(false)
{
	arrowTexture.loadFromFile("Assets/Arrow.png");
	backgroundTexture.loadFromFile("Assets/RedBackground.png");
	pauseBackgroundTexture.loadFromFile("Assets/PauseMenuBackground.png");
	retryTexture.loadFromFile("Assets/RetryButton.png");
	quitTexture.loadFromFile("Assets/QuitButton.png");
	playTexture.loadFromFile("Assets/PlayButton.png");
	mainMenuTexture.loadFromFile("Assets/MainMenuButton.png");
	resumeTexture.loadFromFile("Assets/ResumeButton.png");
	playerHappy.loadFromFile("Assets/PlayerHappy.png");
	playerSad.loadFromFile("Assets/PlayerSad.png");
	enemyHappy.loadFromFile("Assets/EnemyHappy.png");
	enemySad.loadFromFile("Assets/EnemySad.png");
	stonePlatform.loadFromFile("Assets/StonePlatform.png");
	bowTexture.loadFromFile("Assets/Bow.png");
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seeds the rng so it's actually random each time
	leftPlatformSpeedY = (2 + std::rand() % 6);

	#pragma region SetSprites
	// Set Sprites
	player.setTexture(playerHappy);
	enemy.setTexture(enemyHappy);
	platformLeft.setTexture(stonePlatform);
	platformRight.setTexture(stonePlatform);

	bow.setTexture(bowTexture);
	bow.setScale(0.1, 0.1);
	sf::FloatRect bounds = bow.getLocalBounds();
	bow.setOrigin(0.0f, bounds.height / 2.0f);
	#pragma endregion SetSprites

	// Create scoreText
	font.loadFromFile("Assets/Fonts/VerdanaPro-CondRegular.ttf");
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setPosition(25, 0);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setString("Score: " + std::to_string(scoreAmount));

	// Created highscoreText
	highscoreText.setFont(font);
	highscoreText.setCharacterSize(24);
	highscoreText.setPosition(25, 25);
	highscoreText.setFillColor(sf::Color::Red);
	highscoreText.setString("High Score: " + std::to_string(highscoreAmount));

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
	retrySprite.setScale(0.45, 0.45);
	retrySprite.setPosition(280, 510);

	// Create quitSprite
	quitSprite.setTexture(quitTexture);
	quitSprite.setScale(0.45, 0.45);
	quitSprite.setPosition(790, 510);
	#pragma endregion SetupGameOver

	#pragma region SetupMainMenu
	// Create backgroundSprite
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(0.75, 0.75);
	backgroundSprite.setPosition(0, 0);
	
	// Create playSprite
	playSprite.setTexture(playTexture);
	playSprite.setScale(0.45, 0.45);
	playSprite.setPosition(370, 510);
	#pragma endregion SetupMainMenu

	#pragma region SetupPauseMenu
	// Create pauseBackgroundSprite
	pauseBackgroundSprite.setTexture(pauseBackgroundTexture);
	pauseBackgroundSprite.setScale(0.667, 0.667);
	pauseBackgroundSprite.setPosition(0, 0);

	// Create mainMenuSprite
	mainMenuSprite.setTexture(mainMenuTexture);
	mainMenuSprite.setScale(0.45, 0.45);
	mainMenuSprite.setPosition(260, 510);

	// Create resumeSprite
	resumeSprite.setTexture(resumeTexture);
	resumeSprite.setScale(0.45, 0.45);
	resumeSprite.setPosition(315, 340);
	#pragma endregion SetupPauseMenu

	// Creating World
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, 25.0f };
	worldId = b2CreateWorld(&worldDef);

	// Creating Player
	b2BodyDef playerDef = b2DefaultBodyDef();
	playerDef.type = b2_kinematicBody;
	playerDef.position = { 200.0f / worldScale, 237.5f / worldScale };
	playerId = b2CreateBody(worldId, &playerDef);
	b2Polygon playerBox = b2MakeBox(0.5f, 1.0f);

	b2ShapeDef playerShapeDef = b2DefaultShapeDef();
	playerShapeDef.density = 1.0f;
	playerShapeDef.friction = 0.3f;
	playerShapeDef.enableHitEvents = true;
	playerShapeDef.filter.categoryBits = LAYER_PLAYER; // Set collision layer to LAYER_PLAYER
	playerShapeDef.filter.maskBits = 0xFFFF & ~LAYER_ARROW; // Collide with every layer except LAYER_ARROW
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
	enemyShapeDef.enableHitEvents = true;
	enemyShapeDef.filter.categoryBits = LAYER_OTHER; // Set collision layer to LAYER_OTHER
	enemyShapeDef.filter.maskBits = 0xFFFF; // Collide with everything
	b2CreatePolygonShape(enemyId, &enemyShapeDef, &enemyBox);

	// Creating PlatformLeft
	b2BodyDef platformLeftBodyDef = b2DefaultBodyDef();
	platformLeftBodyDef.type = b2_kinematicBody;
	platformLeftBodyDef.position = { 200.0f / worldScale, 300.0f / worldScale };
	platformLeftId = b2CreateBody(worldId, &platformLeftBodyDef);
	
	b2Polygon platformLeftBox = b2MakeBox(1.0f, 0.25f);
	b2ShapeDef platformLeftShapeDef = b2DefaultShapeDef();
	platformLeftShapeDef.enableHitEvents = true;
	platformLeftShapeDef.filter.categoryBits = LAYER_OTHER;
	platformLeftShapeDef.filter.maskBits = 0xFFFF;
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
	platformRightShapeDef.enableHitEvents = true;
	platformRightShapeDef.filter.categoryBits = LAYER_OTHER;
	platformRightShapeDef.filter.maskBits = 0xFFFF;
	b2CreatePolygonShape(platformRightId, &platformRightShapeDef, &platformRightBox);

	// Creating Ground
	b2BodyDef groundBodyDef = b2DefaultBodyDef();
	groundBodyDef.type = b2_kinematicBody;
	groundBodyDef.position = { 640.0f / worldScale, 710.0f / worldScale };
	groundId = b2CreateBody(worldId, &groundBodyDef);

	b2Polygon groundBox = b2MakeBox(12.8f, 0.25f);
	b2ShapeDef groundShapeDef = b2DefaultShapeDef();
	groundShapeDef.enableHitEvents = true;
	groundShapeDef.filter.categoryBits = LAYER_OTHER;
	groundShapeDef.filter.maskBits = 0xFFFF;
	b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

	// Creating WallLeft
	b2BodyDef wallLeftBodyDef = b2DefaultBodyDef();
	wallLeftBodyDef.type = b2_kinematicBody;
	wallLeftBodyDef.position = { 10.0f / worldScale, 50.0f / worldScale };
	wallLeftId = b2CreateBody(worldId, &wallLeftBodyDef);

	b2Polygon wallLeftBox = b2MakeBox(0.25f, 14.4f);
	b2ShapeDef wallLeftShapeDef = b2DefaultShapeDef();
	wallLeftShapeDef.enableHitEvents = true;
	wallLeftShapeDef.filter.categoryBits = LAYER_OTHER;
	wallLeftShapeDef.filter.maskBits = 0xFFFF;
	b2CreatePolygonShape(wallLeftId, &wallLeftShapeDef, &wallLeftBox);

	// Creating WallRight
	b2BodyDef wallRightBodyDef = b2DefaultBodyDef();
	wallRightBodyDef.type = b2_kinematicBody;
	wallRightBodyDef.position = { 1270.0f / worldScale, 50.0f / worldScale };
	wallRightId = b2CreateBody(worldId, &wallRightBodyDef);

	b2Polygon wallRightBox = b2MakeBox(0.25f, 14.4f);
	b2ShapeDef wallRightShapeDef = b2DefaultShapeDef();
	wallRightShapeDef.enableHitEvents = true;
	wallRightShapeDef.filter.categoryBits = LAYER_OTHER;
	wallRightShapeDef.filter.maskBits = 0xFFFF;
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
			canActivateMenu = false;
			clock.StartClock();
			vm.PlaySFX(SoundEffects::Victory);
			enemy.setTexture(enemySad);
			// Increase Score
			scoreAmount += 1;
			scoreText.setString("Score: " + std::to_string(scoreAmount));
			if (scoreAmount >= highscoreAmount && gameOver == false)
			{
				highscoreAmount = scoreAmount;
			}
			highscoreText.setString("High Score: " + std::to_string(highscoreAmount));
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
		vm.PlaySFX(SoundEffects::GameOver);
		gameOver = true;
	}

	// Game Over
	if (gameOver)
	{
		engine.window.draw(gameOverText);
		engine.window.draw(retrySprite);
		engine.window.draw(quitSprite);

		player.setTexture(playerSad);

		// Waits 0.1s before the play button works
		if (clock.WaitForReset(0.1f))
		{
			vm.PlaySFX(SoundEffects::Retry);
			Reset();
			player.setTexture(playerHappy);
			scoreAmount = 0;
			scoreText.setString("Score: " + std::to_string(scoreAmount));
			gameOver = false;
			clock.StopClock();
		}

		// Retry Button
		if (retrySprite.getGlobalBounds().contains(mousePos))
		{
			retrySprite.setColor(sf::Color::Green);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!keyPressedLeftClick)
				{
					clock.StartClock();
					keyPressedLeftClick = true;
				}
			}
			else
			{
				keyPressedLeftClick = false;
			}
		}
		else
		{
			retrySprite.setColor(sf::Color::Red);
		}

		// Quit Button
		if (quitSprite.getGlobalBounds().contains(mousePos))
		{
			quitSprite.setColor(sf::Color::Green);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::cout << "Quit Game" << "\n";
				engine.window.close();
			}
		}
		else
		{
			quitSprite.setColor(sf::Color::Red);
		}
	}

	// Arrow Spawning
	if (!gameOver && !activePauseMenu && !activeMainMenu)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!keyPressedShoot && limitedArrowsAmount >= 1)
			{
				limitedArrowsAmount -= 1;
				limitedArrowsText.setString(std::to_string(limitedArrowsAmount));
				SpawnArrow();
				if (limitedArrowsAmount == 0)
				{
					canActivateMenu = false;
					clock.StartClock();
				}
				keyPressedShoot = true;
			}
		}
		else
		{
			keyPressedShoot = false;
		}
	}

	if (resetKeyEnabled)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			if (!keyPressedReset)
			{
				Reset();
				keyPressedReset = true;
			}
		}
		else
		{
			keyPressedReset = false;
		}
	}

	engine.window.draw(scoreText);
	engine.window.draw(highscoreText);
	engine.window.draw(limitedArrowsText);
	engine.window.draw(limitedArrowSprite);
}

void World::Render()
{
	// Visualising Player
	b2Vec2 playerPos = b2Body_GetPosition(playerId);
	b2Rot playerRot = b2Body_GetRotation(playerId);

	float playerAngle = std::atan2(playerRot.s, playerRot.c) * 180 / 3.14;
	
	sf::Vector2u playerTextureSize = player.getTexture()->getSize();
	sf::Vector2f playerSize(1.0f * worldScale / playerTextureSize.x, 2.0f * worldScale / playerTextureSize.y);
	player.setScale(playerSize);
	player.setOrigin(playerTextureSize.x / 2.0f, playerTextureSize.y / 2.0f);
	player.setPosition(sf::Vector2f(playerPos.x * worldScale, playerPos.y * worldScale));
	player.setRotation(playerAngle);
	engine.window.draw(player);

	// Visualising Enemy
	b2Vec2 enemyPos = b2Body_GetPosition(enemyId);
	b2Rot enemyRot = b2Body_GetRotation(enemyId);

	float enemyAngle = std::atan2(enemyRot.s, enemyRot.c) * 180 / 3.14;

	sf::Vector2u enemyTextureSize = enemy.getTexture()->getSize();
	sf::Vector2f enemySize(1.0f * worldScale / enemyTextureSize.x, 2.0f * worldScale / enemyTextureSize.y);
	enemy.setScale(enemySize);
	enemy.setOrigin(enemyTextureSize.x / 2.0f, enemyTextureSize.y / 2.0f);
	enemy.setPosition(sf::Vector2f(enemyPos.x * worldScale, enemyPos.y * worldScale));
	enemy.setRotation(enemyAngle);
	engine.window.draw(enemy);

	// Platforming Values For Both Platforms
	sf::Vector2u platformTextureSize = platformLeft.getTexture()->getSize();
	sf::Vector2f platformSize(2.0f * worldScale / platformTextureSize.x, 0.5f * worldScale / platformTextureSize.y);

	// Visualizing PlatformLeft
	b2Vec2 platformLeftPosition = b2Body_GetPosition(platformLeftId);
	platformLeft.setScale(platformSize);
	platformLeft.setOrigin(platformTextureSize.x / 2.0f, platformTextureSize.y / 2.0f);
	platformLeft.setPosition(sf::Vector2f(platformLeftPosition.x * worldScale, platformLeftPosition.y * worldScale));
	engine.window.draw(platformLeft);

	// Visualizing PlatformRight
	b2Vec2 platformRightPosition = b2Body_GetPosition(platformRightId);
	platformRight.setScale(platformSize);
	platformRight.setOrigin(platformTextureSize.x / 2.0f, platformTextureSize.y / 2.0f);
	platformRight.setPosition(sf::Vector2f(platformRightPosition.x * worldScale, platformRightPosition.y * worldScale));
	engine.window.draw(platformRight);

	#pragma region Bow
	// Position Bow
	float playerHeight = player.getGlobalBounds().height / worldScale;
	bowPos = sf::Vector2f(playerPos.x * worldScale, playerPos.y * worldScale);
	bow.setPosition(bowPos);

	// Setting Bow rotation to mousePos
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(engine.window);
	sf::Vector2f mousePos = engine.window.mapPixelToCoords(mousePixelPos);

	sf::Vector2f bowDirection = mousePos - bowPos;
	float bowAngle = std::atan2(bowDirection.y, bowDirection.x) * 180 / 3.14;
	
	if (bowAngle >= -60 && bowAngle <= 20)
	{
		bow.setRotation(bowAngle);
		bowRotation = bowAngle;
	}
	engine.window.draw(bow);
	#pragma endregion Bow

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
	std::cout << "Spawned in Arrow" << "\n";
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

	// Reset limitedArrowsAmount
	limitedArrowsAmount = 5;
	limitedArrowsText.setString(std::to_string(limitedArrowsAmount));
	clock.StopClock();

	// Set random position and speed of platformRightId
	float randomX = 13.0f + static_cast<float>(std::rand()) / (RAND_MAX / (21.6f - 13.0f));
	float randomY = 4.4f + static_cast<float>(std::rand()) / (RAND_MAX / (10.0f - 4.4f));
	b2Body_SetTransform(platformRightId, { randomX, randomY }, b2MakeRot(0.0f));
	rightPlatformSpeedY = (2 + std::rand() % 10);
	
	// Platform will always spawn while moving upwards, never downwards
	rightPlatformSpeedY *= -1;

	// Position enemy above platform
	b2Body_SetTransform(enemyId, { randomX, randomY-1.2f }, b2MakeRot(0.0f));
	
	// Change enemy sprite to enemyHappy
	enemy.setTexture(enemyHappy);

	// Can press "Escape" to open pause menu
	canActivateMenu = true;
}

void World::PauseMenu()
{
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(engine.window);
	sf::Vector2f mousePos = engine.window.mapPixelToCoords(mousePixelPos);

	engine.window.draw(pauseBackgroundSprite);
	engine.window.draw(mainMenuSprite);
	engine.window.draw(resumeSprite);
	engine.window.draw(quitSprite);

	// Waits 0.1s before the play button works
	if (clock.WaitForReset(0.1f))
	{
		activePauseMenu = false;
		clock.StopClock();
	}

	// Main Menu Button
	if (mainMenuSprite.getGlobalBounds().contains(mousePos))
	{
		mainMenuSprite.setColor(sf::Color::Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!keyPressedLeftClick)
			{
				activePauseMenu = false;
				activeMainMenu = true;
				keyPressedLeftClick = true;
			}
		}
		else
		{
			keyPressedLeftClick = false;
		}
	}
	else
	{
		mainMenuSprite.setColor(sf::Color::Red);
	}

	// Resume Button
	if (resumeSprite.getGlobalBounds().contains(mousePos))
	{
		resumeSprite.setColor(sf::Color::Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!keyPressedLeftClick)
			{
				clock.StartClock();
				keyPressedLeftClick = true;
			}
		}
		else
		{
			keyPressedLeftClick = false;
		}
	}
	else
	{
		resumeSprite.setColor(sf::Color::Red);
	}

	// Quit Button
	if (quitSprite.getGlobalBounds().contains(mousePos))
	{
		quitSprite.setColor(sf::Color::Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::cout << "Quit Game" << "\n";
			engine.window.close();
		}
	}
	else
	{
		quitSprite.setColor(sf::Color::Red);
	}
}

void World::MainMenu()
{
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(engine.window);
	sf::Vector2f mousePos = engine.window.mapPixelToCoords(mousePixelPos);

	engine.window.draw(backgroundSprite);
	engine.window.draw(playSprite);
	engine.window.draw(quitSprite);

	// Waits 0.1s before the play button works
	if (clock.WaitForReset(0.1f))
	{
		vm.PlaySFX(SoundEffects::Retry);
		activeMainMenu = false;
		clock.StopClock();
	}

	// Play Button
	if (playSprite.getGlobalBounds().contains(mousePos))
	{
		playSprite.setColor(sf::Color::Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!keyPressedLeftClick)
			{
				clock.StartClock();
				keyPressedLeftClick = true;
			}
		}
		else
		{
			keyPressedLeftClick = false;
		}
	}
	else
	{
		playSprite.setColor(sf::Color::Red);
	}

	// Quit Button
	if (quitSprite.getGlobalBounds().contains(mousePos))
	{
		quitSprite.setColor(sf::Color::Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::cout << "Quit Game" << "\n";
			engine.window.close();
		}
	}
	else
	{
		quitSprite.setColor(sf::Color::Red);
	}
}

void World::ToggleMenu()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && canActivateMenu)
	{
		if (!keyPressedEscape)
		{
			if (activePauseMenu || activeMainMenu)
			{
				std::cout << "Menu Disabled" << "\n";
				activePauseMenu = false;
				activeMainMenu = false;
				keyPressedEscape = true;
			}
			else
			{
				std::cout << "Pause Menu Enabled" << "\n";
				activePauseMenu = true;
				keyPressedEscape = true;
			}
		}
	}
	else
	{
		keyPressedEscape = false;
	}
}