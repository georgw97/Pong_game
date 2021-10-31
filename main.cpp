#include <SFML/Graphics.hpp>
#include <iostream>

float deltaT(sf::Clock clock){  
    return clock.getElapsedTime().asSeconds();
}

int main()
{
    //Game variables

    float playerMoveSpeed = 1000;
    float playerMoveY = 0;
    float ballMovementSpeedX = 1000;
    float ballMovementSpeedY = 100;
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
            // key pressed keybinds
            if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::S){
                    playerMoveY = playerMoveSpeed;
                }
                else if(event.key.code == sf::Keyboard::W){
                    playerMoveY = -playerMoveSpeed;
                }
            }           
            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::S){
                    playerMoveY = 0;
                }
                else if(event.key.code == sf::Keyboard::W){
                    playerMoveY = 0;
                }
            }
        }

        // player and ball need to move
        player1.move(sf::Vector2f(0, playerMoveY * deltaT(sclock)));
        ball.move(sf::Vector2f(ballMovementSpeedX * deltaT(sclock), ballMovementSpeedY * deltaT(sclock)));

        // restart clock
        sf::Time elapsed = sclock.restart();

        // Player Out of Scope handling


        // Ball bouncing handling
        if(ball.getPosition().x >= 1280 + 30){
            ballMovementSpeedX = -ballMovementSpeedX;
        }
        if(ball.getPosition().y >= resVer + 30 || (ball.getPosition().y <= 0 + 45)){
            ballMovementSpeedY = -ballMovementSpeedY;
        }
        // player missed ball handling
        if(ball.getPosition().x <= 0){
            window.close();
        }

        //collision handling
        if(ball.getGlobalBounds().intersects(player1.getGlobalBounds())){
            ballMovementSpeedX = -ballMovementSpeedX;

            //check where the ball exactly intersects with the player

            //change ball direction depending from the pos where the ball hit player
        
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