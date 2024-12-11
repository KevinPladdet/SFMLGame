#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Insane game");
    sf::Texture texture;
    sf::Sprite sprite;

    // Ints for moving the sprite
    int changeX = 0;
    int changeY = 0;
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
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255, 255, 255));
        window.draw(sprite);
        window.display();


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
        {
            changeY -= 2;
            std::cout << "changeY = " << changeY << "\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            changeY += 2;
            std::cout << "changeY = " << changeY << "\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            changeX -= 2;
            std::cout << "changeX = " << changeX << "\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            changeX += 2;
            std::cout << "changeX = " << changeX << "\n";
        }
    }
    return 0;
}