#include <iostream>
#include <SFML/Graphics.hpp>
#include "funcs.hpp"

float deltaT(sf::Clock clock){  
    return clock.getElapsedTime().asSeconds();
}



void restartGame(int &points, int &ballMovementSpeedX, int &ballMovementSpeedY, int &resHor, int &resVer, sf::Text &pointstext, sf::CircleShape &ball){
    points = 0;
    pointstext.setString(std::to_string(points));
    ball.setPosition(sf::Vector2f(resHor/2, resVer/2));
    ballMovementSpeedX = 1000;
    ballMovementSpeedY = 50 - (rand() % 100);
}

void mainMenu(){

}

void singlePlayerGameStart(){

}

class Player{

};

class GameState{
    public:
        int points;
        int life;
        int ballMovementSpeedX = 1000;
        int ballMovementSpeedY = 50 - (rand() % 100);
        int player;
    GameState(){

    }
};

namespace gw{
    class Text{

    };
}