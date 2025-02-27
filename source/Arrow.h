#pragma once
#include "box2d/box2d.h"
#include <SFML/Graphics.hpp>

class Engine;
class World;
class VolumeManager;
class Arrow
{
public:
	Arrow(Engine& engine, World& world, VolumeManager& vm);
	void LoadSprite();
	void CreateArrowBody();
	void Render();
	void DestroyArrow();
	void Update();
	void ArrowForce();

private:
	Engine& engine;
	World& world;
	VolumeManager& vm;

	// Force
	b2Vec2 forcePosition;
	bool keyPressed;

	// b2BodyId
	b2BodyId arrowId;

	// Arrow
	sf::Sprite arrowSprite;
};