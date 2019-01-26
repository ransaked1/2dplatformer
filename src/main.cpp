#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "2dplat.h"

using namespace std;

/*TO DO!
-coment platform generator
-use advanced physics without hardcode
-change how the camera follows the player
-prepare input for pluging in NN
*/

int main()
{
	/***********************\
	**** INITIALIZATIONS ****
	\***********************/

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(720, 720), "SFML 2D Platformer!");	//initializing window size and name
	window.setVerticalSyncEnabled(false);																			//disabling vertical sync
	sf::View view(sf::FloatRect(50.f, 100.f, 500.f, 500.f));                  //initializing the field of view

	sf::Clock clock;	//initializing the clock
	sf::Time	time;		//initializing the time variable
	sf::Int64 msec;		//the time is going to be converted to microseconds

	sf::RectangleShape player;			//creating the controllable shape
	player.setSize(sf::Vector2f(50, 25));
	player.setPosition(50, 390);
	player.setFillColor(sf::Color::Red);

	float windowSizeX;
	float	windowSizeY;
	float scalerX = 1.0;		//initializing scaler for x coordonates
	float scalerY = 1.0;		//initializing scaler for y coordonates

	std::vector<sf::RectangleShape> groundList;		//creating the ground vector

	sf::RectangleShape ground;			//the long ground object
	ground.setSize(sf::Vector2f(1000, 30));
	ground.setPosition(0, 400);

	sf::RectangleShape ground2;			//a platform
	ground2.setSize(sf::Vector2f(150, 30));
	ground2.setPosition(200, 310);

	sf::RectangleShape ground3;			//a platform
	ground3.setSize(sf::Vector2f(150, 30));
	ground3.setPosition(1100, 340);

	groundList.push_back(ground);		//putting the predefined init ground objects
	groundList.push_back(ground2);
	groundList.push_back(ground3);

	bool onGround;								//Is the player on the ground?
	bool inAir;										//Is the player going against the gravity?
	bool gameOn = false;									//Is the game stopped?

	double gravity;   //global gravity always positive nr (going down)
	double velocityX = 3;					//player velocity in X direction
	double velocityY = 0;					//player velocity in Y direction

	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");		//scoring text setup
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(25);

	int score = 0;
	float gameSpeed = 3;

	//infinite loop while window is open
	while (window.isOpen())
	{
		windowSizeX = window.getSize().x;
		windowSizeY = window.getSize().y;

		scalerX = windowSizeX / 720;
		scalerY = windowSizeY / 720;

		gravity = GRAVITY * scalerY;

		time = clock.getElapsedTime();
		msec = time.asMicroseconds();

		sf::Event event;	//event is a buffer checking key states

		//checking if there is any button pressed before updating the frame
		if(msec > 200){
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				break;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && onGround == true) //can jump only once when on the ground
			{
					velocityY = -19 * scalerY;
					onGround = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //can jump only once when on the ground
					gameOn = true;
		}

		//applying physics over time
		time = clock.getElapsedTime();
		msec = time.asMicroseconds();

		if (msec > 1 && gameOn)
		applyPhysics(&player, &velocityY, &onGround, &inAir, gravity, velocityX, scalerY, &gameOn);

		if (time.asSeconds() > 30)
			velocityX = 3.5;
		if (time.asSeconds() > 30 && time.asSeconds() > 60)
			velocityX = 4;
		if (time.asSeconds() > 30 && time.asSeconds() > 60 && time.asSeconds() > 120)
			velocityX = 4.5;

		//Checking if player is intersection a ground object and verifying if its over the ground
		//for the next iteration
		onGround = false;
		for (int i = 0; i <= groundList.size() - 1; i++)
		{
			if (player.getGlobalBounds().intersects(groundList[i].getGlobalBounds()) && groundList[i].getPosition().y -1 - (player.getSize().y - 0.1)
				< player.getPosition().y && groundList[i].getPosition().y > player.getPosition().y)
			{
				player.setPosition(player.getPosition().x, groundList[i].getPosition().y - (player.getSize().y - 0.1));
				onGround = true;
			}
		}

		if (!gameOn)
		{
			groundList.clear();
			groundList.push_back(ground);		//putting the predefined init ground objects
			groundList.push_back(ground3);
		}
		else
			groundList = generatePlatforms(player, groundList, velocityX); //generating the new ground list

		//debuging
		//cout << player.getPosition().x << " " << player.getPosition().y << endl;
		//cout << groundList[0].getPosition().x << " " << groundList[0].getPosition().y << endl;
		//cout << "onGround: " << onGround << "   " << "inAir: " << inAir << endl;
		//std::cout << groundList.size() << endl;
		//cout << scalerX << " " << scalerY << endl;
		//cout << velocityX << " " << velocityY << endl;

		//post processing
		view.setCenter(player.getPosition().x + 110, player.getPosition().y - 20); 		//set screen following player

		score = (player.getPosition().x - 50) / 100;  //scoring formula
		text.setString("Score: " + to_string(score));
		text.setPosition(player.getPosition().x - 120, player.getPosition().y - 300);	// print score and follow the player

		window.setView(view); //set scene
		window.clear();				//clear scene

		window.draw(player);	//set objects to be drawn
		for (int i = 0; i <= groundList.size() - 1; i++)
			window.draw(groundList[i]);
		window.draw(text);

		window.display();			//draw the scene
		clock.restart();			//restarting clock
	}
	}
	return 0;
}
