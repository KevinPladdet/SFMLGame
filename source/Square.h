#pragma once
#include <SFML/Graphics.hpp>

class Engine;
class Square
{
public:
	Square(Engine& engine);
	void Update();
	void LoadSprite(std::string path);
private:
	sf::RectangleShape squareVisual;
	sf::Vector2f squarePos;
	float velocityX;
	float velocityY;

	Engine& engine;

	sf::Texture texture;
	sf::Sprite sprite;
};