#pragma once
#include <SFML/Graphics.hpp>

class Engine;
class Dvd
{
public:
	Dvd(Engine& engine);
	void Update();
	void LoadSprite(std::string path);
	void DisplayText();

	// BounceText
	sf::Font font;
	sf::Text text;
	int bounceAmount;
private:
	Engine& engine;

	// Movement
	float velocityX;
	float velocityY;

	// Dvd Logo
	sf::Vector2f spritePosition;
	sf::Texture texture;
	sf::Sprite sprite;
};