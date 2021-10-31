#include <SFML/Graphics.hpp>
#include <iostream>

float deltaT(sf::Clock clock){  
    return clock.getElapsedTime().asSeconds();
}

int main()
{
    //Game variables

    float playerMoveSpeed = 100;
    float ballMovementSpeedX = 100 *(rand() % 3+1);
    float ballMovementSpeedY = 100 *(rand() % 3+1);
    int resHor = 1280;
    int resVer = 720;
    bool condition = false;

    // create the clock
    sf::Clock sclock;

    // create the Windo
    sf::RenderWindow window(sf::VideoMode(resHor, resVer), "My Window");

    // create the texture
    sf::Texture playertexture;
    // it shall be a 16x1600 texture, empty
    if (!playertexture.loadFromFile("testtexture.png", sf::IntRect(0, 0 , 10 , 100)))
    {
        // error...
        return 1;
    }
    // create the player
    sf::Sprite player1;
    player1.setTexture(playertexture);
    player1.setPosition(sf::Vector2f(10.f, 50.f));

    //create the ball
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color(250, 250, 250));
    ball.setPosition(sf::Vector2f(resHor/2, resVer/2));
    ball.setOrigin(50, 50);

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
                    player1.move(sf::Vector2f(0.f, playerMoveSpeed));
                }
                if (event.key.code == sf::Keyboard::W){
                    player1.move(sf::Vector2f(0.f, -playerMoveSpeed));
                }
            }           
        }

        ball.move(sf::Vector2f(ballMovementSpeedX * deltaT(sclock), ballMovementSpeedY * deltaT(sclock)));
        sf::Time elapsed = sclock.restart();
        std::cout << ballMovementSpeedX << std::endl;
        if (ball.getPosition().x >= 1280 + 30){
            ballMovementSpeedX = -ballMovementSpeedX;
        }
        if (ball.getPosition().y >= resVer + 30 || (ball.getPosition().y <= 0 + 45)){
            ballMovementSpeedY = -ballMovementSpeedY;
        }
        if (ball.getGlobalBounds().intersects(player1.getGlobalBounds())){
            ballMovementSpeedX = -ballMovementSpeedX;
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
        // draw everything here
        window.draw(ball);
        window.draw(player1);

        //to here
        window.display();
    }   
    return 0;
}