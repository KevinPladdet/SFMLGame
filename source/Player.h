#pragma once
#include <SFML/Graphics.hpp>

class Engine;
class Player
{
public:
	Player(Engine& engine);
private:
	Engine& engine;
};