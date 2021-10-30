#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // create the Windo
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My Window");

    // create the texture
    sf::Texture texture;
    // it shall be a 200x100 texture, empty
    if (!texture.loadFromFile("testtexture.png", sf::IntRect(0, 0 , 16 , 160)))
    {
        // error...
    }

    // create the texutre
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(10.f, 50.f));

    //Game variables
    float playerMoveSpeed = 5;
    //game loop
    while(window.isOpen()){

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while(window.pollEvent(event)){
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::S){
                    sprite.move(sf::Vector2f(0.f, playerMoveSpeed));
                }
                if (event.key.code == sf::Keyboard::W){
                    sprite.move(sf::Vector2f(0.f, -playerMoveSpeed));
                }
            }
        }
        // clear the window with black color
        window.clear(sf::Color::Black);
        // draw everything here
        window.draw(sprite);

        //to here
        window.display();
    }   
    return 0;
}