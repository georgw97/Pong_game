#include <SFML/Graphics.hpp>
#include <iostream>
#include "time.hpp"

static sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong");
static sf::Clock sclock;
static sf::Clock collisionClock;
static sf::Font font;
static sf::Texture playertexture;

class Game
{
private:


public:
	// Game Variables 
	//Graphics
	int resHor = 1280;
	int resVer = 720;

	// Game state
	int points = 0;
	int life = 0;

	// Player Variables
	float playerMoveSpeed; // speed at which the Player tavels
	float playerMoveY; // how much the player moves (specified in loop)
	float playerHeight = 100.0;
	float playerWidth = 10.0;
	//
	bool gameOn = false;
};

Game game;

bool Initialize()
{


	if(!font.loadFromFile("../fonts/CascadiaMono.ttf"))
	{
		return -1;
	}

	if(!playertexture.loadFromFile("../textures/testtexture.png", sf::IntRect(0, 0, game.playerWidth, game.playerHeight)))
	{
		return -1;
	}
}

void MainMenu()
{

}



void RunGame()
{
	//check if initialized and running


	//Game variables
	game.playerMoveSpeed = 1000.0; // speed
	game.playerMoveY = 0.0; // how much the player moves (specified in loop)


	//initial movement of ball
	float ballMovementSpeedX = 1000.0;
	srand(time(0));
	float ballMovementSpeedY = 50 - (rand() % 100);

	// Init the main Menu
	sf::Text mainMenuText;
	mainMenuText.setFont(font);
	mainMenuText.setString("WELCOME To Pong Game -- Made by Georg Wollert\n\n"
		"1: Single Player\n"
		"2: Multi Player\n"
		"3: Highscore\n"
		"4: Quit\n");
	mainMenuText.setCharacterSize(24);
	mainMenuText.setFillColor(sf::Color::White);
	mainMenuText.setPosition(sf::Vector2f(10, 10));
	mainMenuText.setOrigin(sf::Vector2f());

	// Init the text
	sf::Text pointstext;
	pointstext.setFont(font);
	pointstext.setString(std::to_string(game.points));
	pointstext.setCharacterSize(24);
	pointstext.setFillColor(sf::Color::White);
	pointstext.setPosition(sf::Vector2f(game.resHor * 0.5, 0 + 10));

	// create the player
	sf::Sprite player1;
	player1.setTexture(playertexture);
	player1.setPosition(sf::Vector2f(10.f, game.resVer / 2));
	player1.setOrigin(5, game.playerHeight / 2.0);

	//create the ball
	sf::CircleShape ball(10.f);
	ball.setFillColor(sf::Color(250, 250, 250));
	ball.setPosition(sf::Vector2f(game.resHor / 2, game.resVer / 2));
	ball.setOrigin(5, 5);

	//Start loop
	//game loop
	while(window.isOpen())
	{

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while(window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			// Game 1
			// key pressed keybinds
			if(event.type == sf::Event::KeyPressed)
			{
				//Main menu Logic
				if(!game.gameOn)
				{
					if(event.key.code == sf::Keyboard::Num1)
					{
						game.points = 0;
						pointstext.setString(std::to_string(game.points));
						ball.setPosition(sf::Vector2f(game.resHor / 2, game.resVer / 2));
						ballMovementSpeedX = 1000;
						ballMovementSpeedY = 50 - (rand() % 100);
						game.gameOn = true;
					}
					else if(event.key.code == sf::Keyboard::Num2)
					{

					}
					else if(event.key.code == sf::Keyboard::Num3)
					{
						//Disp highscore from database
					}
					else if(event.key.code == sf::Keyboard::Num4)
					{
						window.close();
					}
					else if(event.key.code == sf::Keyboard::Escape)
					{
						window.close();
					}
				}
				//Game Logic
				if(game.gameOn)
				{
					if(event.key.code == sf::Keyboard::S)
					{
						game.playerMoveY = game.playerMoveSpeed;
					}
					else if(event.key.code == sf::Keyboard::W)
					{
						game.playerMoveY = -game.playerMoveSpeed;
					}
					else if(event.key.code == sf::Keyboard::Escape)
					{
						game.gameOn = false;
					}

				}
			}
			if(event.type == sf::Event::KeyReleased)
			{
				if(event.key.code == sf::Keyboard::S)
				{
					game.playerMoveY = 0;
				}
				else if(event.key.code == sf::Keyboard::W)
				{
					game.playerMoveY = 0;
				}
			}
		}
		// Player Out of Scope handling
		if(player1.getPosition().y > game.resVer - game.playerHeight / 2.0)
		{
			player1.setPosition(sf::Vector2f(10, game.resVer - game.playerHeight / 2.0));
		}
		else if(player1.getPosition().y <= 0 + game.playerHeight / 2.0)
		{
			player1.setPosition(sf::Vector2f(10, game.playerHeight / 2.0));
		}

		// Ball bouncing handling
		if(ball.getPosition().x >= 1280)
		{
			ballMovementSpeedX = -ballMovementSpeedX;
		}
		else if(ball.getPosition().y >= game.resVer - 15 || (ball.getPosition().y <= 0))
		{
			ballMovementSpeedY = -ballMovementSpeedY;
		}
		// player missed ball handling
		else if(ball.getPosition().x <= 0)
		{
			//Restart
			game.points = 0;
			pointstext.setString(std::to_string(game.points));
			ball.setPosition(sf::Vector2f(game.resHor / 2, game.resVer / 2));
			ballMovementSpeedX = 1000;
			ballMovementSpeedY = 50 - (rand() % 100);
		}

		//collision handling
		if(ball.getGlobalBounds().intersects(player1.getGlobalBounds()))
		{
			//check if 1 second has passed since last collision
			if(collisionClock.getElapsedTime().asSeconds() > 1)
			{
				collisionClock.restart();
				//increment points 
				game.points++;
				pointstext.setString(std::to_string(game.points));
				//check where the ball exactly intersects with the player
				float ballPosY = ball.getPosition().y;
				float playerPosY = player1.getPosition().y;
				//change ball direction depending from the pos where the ball hit player
				//player is 10 x 100, ball is r10
				float param = playerPosY - ballPosY;
				float rise = 1.0 / 100.0;
				// Bug 
				ballMovementSpeedY = rise * param * ballMovementSpeedX;
				ballMovementSpeedX = -ballMovementSpeedX;
			}
		}

		// player and ball need to move
		player1.move(sf::Vector2f(0, game.playerMoveY * deltaT(sclock)));
		ball.move(sf::Vector2f(ballMovementSpeedX * deltaT(sclock), ballMovementSpeedY * deltaT(sclock)));

		// restart clock
		sf::Time elapsed = sclock.restart();

		// clear the window with black color
		window.clear(sf::Color::Black);
		// draw everything here
		if(game.gameOn)
		{
			window.draw(ball);
			window.draw(player1);
			window.draw(pointstext);
		}
		else
		{
			window.draw(mainMenuText);
		}

		//to here
		window.display();
	}

}



int main()
{
	Initialize();
	MainMenu();
	RunGame();

	
	return 0;
}