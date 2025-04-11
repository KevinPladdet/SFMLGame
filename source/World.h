#pragma once
#include "box2d/box2d.h"
#include <SFML/Graphics.hpp>
#include "Arrow.h"
// Collision Layers
constexpr uint16_t LAYER_PLAYER = 0x0001;
constexpr uint16_t LAYER_ARROW = 0x0002;
constexpr uint16_t LAYER_OTHER = 0x0003;

class Engine;
class VolumeManager;
class Clock;
class World
{
public:
	World(Engine& engine, VolumeManager& vm, Clock& clock);
	void Update();
	void Render();
	void SpawnArrow();
	void DestroyArrows();
	void Reset();

	// worldId is used to spawn body's in the world
	b2WorldId worldId;

	// worldScale is 50 because 50 pixels is 1 meter in Box2D
	const int worldScale = 50;

	// Arrow Texture
	sf::Texture arrowTexture;
	
	// Bow position and rotation for Arrow.cpp to use
	sf::Vector2f bowPos;
	float bowRotation;

private:
	Engine& engine;
	VolumeManager& vm;
	Clock& clock;

	std::vector<Arrow> arrows;
	
	bool keyPressedK;
	bool keyPressedR;
	bool waitForReset;

	// b2BodyId
	b2BodyId playerId;
	b2BodyId enemyId;

	b2BodyId platformLeftId;
	b2BodyId platformRightId;

	b2BodyId groundId;
	b2BodyId wallLeftId;
	b2BodyId wallRightId;
	
	// Visualising shapes
	sf::Sprite player;
	sf::Texture playerHappy;
	sf::Texture playerSad;

	sf::Sprite enemy;
	sf::Texture enemyHappy;
	sf::Texture enemySad;

	sf::Sprite platformLeft;
	sf::Sprite platformRight;
	sf::Texture stonePlatform;

	sf::Sprite bow;
	sf::Texture bowTexture;

	sf::RectangleShape ground;
	sf::RectangleShape wallLeft;
	sf::RectangleShape wallRight;
	
	// World values
	float timeStep = 1.0f / 150.0f;
	int subStepCount = 4;

	// Moving Platform
	float leftPlatformSpeedY;
	float rightPlatformSpeedY;
	float minY;
	float maxY;

	// Score
	sf::Font font;
	sf::Text scoreText;
	int scoreAmount;
	sf::Text highscoreText;
	int highscoreAmount;

	// Limited Arrows
	sf::Text limitedArrowsText;
	sf::Sprite limitedArrowSprite;
	int limitedArrowsAmount;

	// Game Over
	sf::Text gameOverText;
	bool gameOver;
	sf::Sprite retrySprite;
	sf::Texture retryTexture;
	sf::Sprite quitSprite;
	sf::Texture quitTexture;
};