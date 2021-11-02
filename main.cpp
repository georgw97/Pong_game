#include <SFML/Graphics.hpp>
#include <iostream>

float deltaT(sf::Clock clock){  
    return clock.getElapsedTime().asSeconds();
}

int main()
{
    //game res
    int resHor = 1280;
    int resVer = 720;

    //Game variables
    float playerMoveSpeed = 1000.0; // speed
    float playerMoveY = 0.0; // how much the player moves (specified in loop)
    float playerHeight = 100.0;
    float playerWidth = 10.0;

    //initial movement of ball
    float ballMovementSpeedX = 1000.0; 
    srand(time(0));
    float ballMovementSpeedY = 50 - (rand() % 100);

    //pointcounter
    int points = 0;
    int life = 0;

    //create the text font
    sf::Font font;
    if(!font.loadFromFile("CascadiaMono.ttf")){
        return 2;
    }

    //crate the text
    sf::Text pointstext;
    pointstext.setFont(font);
    pointstext.setString(std::to_string(points));
    pointstext.setCharacterSize(24);
    pointstext.setFillColor(sf::Color::White);
    pointstext.setPosition(sf::Vector2f(resHor * 0.5, 0+ 10));
    sf::Text lifetext;

    // create the clock
    sf::Clock sclock;
    sf::Clock collisionClock;

    // create the Windo
    sf::RenderWindow window(sf::VideoMode(resHor, resVer), "My Window");

    // create the texture
    sf::Texture playertexture;
    // it shall be a 16x1600 texture, empty
    if (!playertexture.loadFromFile("testtexture.png", sf::IntRect(0, 0 , playerWidth , playerHeight)))
    {
        // error...
        return 1;
    }
    // create the player
    sf::Sprite player1;
    player1.setTexture(playertexture);
    player1.setPosition(sf::Vector2f(10.f, resVer/2));
    player1.setOrigin(5, playerHeight/2.0);

    //create the ball
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color(250, 250, 250));
    ball.setPosition(sf::Vector2f(resHor/2, resVer/2));
    ball.setOrigin(5, 5);

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
        // Player Out of Scope handling
        if(player1.getPosition().y > resVer-playerHeight/2.0){
            player1.setPosition(sf::Vector2f(10, resVer - playerHeight/2.0));
        }
        else if(player1.getPosition().y <= 0 + playerHeight/2.0){
            player1.setPosition(sf::Vector2f(10, playerHeight/2.0));
        }

        // Ball bouncing handling
        if(ball.getPosition().x >= 1280){
            ballMovementSpeedX = -ballMovementSpeedX;
        }
        else if(ball.getPosition().y >= resVer - 15 || (ball.getPosition().y <= 0 )){
            ballMovementSpeedY = -ballMovementSpeedY;
        }
        // player missed ball handling
        else if(ball.getPosition().x <= 0){
            //Restart
            points = 0;
            pointstext.setString(std::to_string(points));
            ball.setPosition(sf::Vector2f(resHor/2, resVer/2));
            ballMovementSpeedX = 1000;
            ballMovementSpeedY = 50 - (rand() % 100);
            std::cout << "ball is out!" << std::endl;

        }

        //collision handling
        if(ball.getGlobalBounds().intersects(player1.getGlobalBounds())){
            //check if 1 second has passed since last collision
            if(collisionClock.getElapsedTime().asSeconds() > 1){
                collisionClock.restart();
                //increment points 
                points++;
                pointstext.setString(std::to_string(points));
                //check where the ball exactly intersects with the player
                float ballPosY = ball.getPosition().y;
                float playerPosY = player1.getPosition().y;
                //change ball direction depending from the pos where the ball hit player
                //player is 10 x 100, ball is r10
                float param = playerPosY-ballPosY;
                float rise = 1.0/50.0;
                // Bug 
                ballMovementSpeedY = rise * param * ballMovementSpeedX;
                ballMovementSpeedX = -ballMovementSpeedX;
            } 
        }
    
        // player and ball need to move
        player1.move(sf::Vector2f(0, playerMoveY * deltaT(sclock)));
        ball.move(sf::Vector2f(ballMovementSpeedX * deltaT(sclock), ballMovementSpeedY * deltaT(sclock)));

        // restart clock
        sf::Time elapsed = sclock.restart();

        // clear the window with black color
        window.clear(sf::Color::Black);
        // draw everything here
        window.draw(ball);
        window.draw(player1);
        window.draw(pointstext);

        //to here
        window.display();
    }   
    return 0;
}