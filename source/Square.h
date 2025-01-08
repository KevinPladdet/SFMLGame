#pragma once
#include <SFML/Graphics.hpp>

class Engine;
class Square
{
public:
	Square(Engine& engine);
	void Update();
	void LoadSprite(std::string path);
	//void DisplayPath()
	// make the text in square tomorrow

	// BounceText
	sf::Font font;
	sf::Text text;
	int bounceAmount;
private:
	// Square
	sf::RectangleShape squareVisual;
	sf::Vector2f squarePos;
	float velocityX;
	float velocityY;

	Engine& engine;

	// Dvd Logo
	sf::Vector2f spritePosition;
	sf::Texture texture;
	sf::Sprite sprite;

	
};