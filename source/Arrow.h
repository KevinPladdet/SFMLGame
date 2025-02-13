#pragma once
#include "box2d/box2d.h"
#include <SFML/Graphics.hpp>

class Engine;
class World;
class Arrow
{
public:
	Arrow(Engine& engine, World& world);
	void LoadSprite();
	void CreateArrowBody();
	void Render();
	void DestroyArrow();

private:
	Engine& engine;
	World& world;

	// b2BodyId
	b2BodyId arrowId;

	// Arrow
	sf::Sprite arrowSprite;
};