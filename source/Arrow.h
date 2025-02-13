#pragma once
#include "box2d/box2d.h"
#include <SFML/Graphics.hpp>

class Engine;
class World;
class Arrow
{
public:
	Arrow(Engine& engine, World& world);
	void LoadSprite(std::string path);
	void CreateArrowBody();
	void Render();

private:
	Engine& engine;
	World& world;

	// b2BodyId
	b2BodyId arrowId;

	// Arrow
	sf::Texture texture;
	sf::Sprite arrowSprite;
};