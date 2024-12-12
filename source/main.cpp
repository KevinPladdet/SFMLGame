#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Time.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Insane game");
    sf::Texture texture;
    sf::Sprite sprite;

    // float for moving the sprite
    float posX = 0;
    float posY = 0;
    float speed = 200;

    std::string movementDirection;
    
    std::string path = "Assets/Jinx.jpg";

    if (texture.loadFromFile("Assets/Jinx.jpg"))
    {
        std::cout << "Succesfully loaded " << path << "\n";
    }

    sprite.setTexture(texture);

    // Resize sprite to pixelSize
    int size = texture.getSize().x;
    int pixelSize = 400;
    float scale = (float)pixelSize / (float)size;
    sprite.setScale(scale, scale);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        Engine::Time::UpdateTime();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
        {
            posY -= 1 * speed * Engine::Time::deltaTime;
            sprite.setPosition(posX, posY);
            std::cout << "posY = " << posY << "\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            posY += 1 * speed * Engine::Time::deltaTime;
            sprite.setPosition(posX, posY);
            std::cout << "posY = " << posY << "\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            posX -= 1 * speed * Engine::Time::deltaTime;
            sprite.setPosition(posX, posY);
            std::cout << "posX = " << posX << "\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            posX += 1 * speed * Engine::Time::deltaTime;
            sprite.setPosition(posX, posY);
            std::cout << "posX = " << posX << "\n";
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sprite.setPosition(0, 0);
        }

        window.clear(sf::Color(255, 255, 255));
        window.draw(sprite);
        window.display();
    }
    return 0;
}