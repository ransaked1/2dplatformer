#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "2dplat.h"

using namespace std;

/*TO DO!
-put things into objects
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
	window.setFramerateLimit(60);																		//disabling vertical sync
	sf::View view(sf::FloatRect(50.f, 100.f, 500.f, 500.f));                  //initializing the field of view

	sf::Clock clock;	//initializing the game clock
	sf::Clock speedClock;
	sf::Time	speedTime;
	sf::Time	time;		//initializing the time variable
	sf::Int64 msec;		//the time is going to be converted to microseconds

	float windowSizeX;
	float	windowSizeY;
	float scalerX = 1.0;		//initializing scaler for x coordonates

	std::vector<sf::RectangleShape> groundList = setupStartPoint();		//creating the ground vector

	playerObject playerObject;

	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");		//scoring text setup
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(25);

	int score = 0;

	//infinite loop while window is open
	while (window.isOpen())
	{
		windowSizeX = window.getSize().x;
		windowSizeY = window.getSize().y;

		scalerX = windowSizeX / 720;
		playerObject.scalerY = windowSizeY / 720;

		playerObject.setGravity();

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

				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && playerObject.onGround == true) //can jump only once when on the ground
				{
					playerObject.velocityY = -19 * playerObject.scalerY;
					playerObject.onGround = false;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //starting the game with spacebar
				{
					playerObject.gameOn = true;
					speedClock.restart();
				}
			}

				//applying physics over time
			time = clock.getElapsedTime();
			msec = time.asMicroseconds();

			if (msec > 1 && playerObject.gameOn)
				applyPhysics(&playerObject);

			speedTime = speedClock.getElapsedTime();
			if (speedTime.asSeconds() > 15)
				playerObject.velocityX = 5;
			else if (speedTime.asSeconds() > 30)
				playerObject.velocityX = 7;
			else if (speedTime.asSeconds() > 60)
				playerObject.velocityX = 10;
			else
				playerObject.velocityX = 4;

			//Checking if player is intersection a ground object and verifying if its over the ground
			//for the next iteration
			playerObject.onGround = false;
			for (int i = 0; i <= groundList.size() - 1; i++)
			{
				if (playerObject.player.getGlobalBounds().intersects(groundList[i].getGlobalBounds()) && groundList[i].getPosition().y -1 - (playerObject.player.getSize().y - 0.1)
					< playerObject.player.getPosition().y && groundList[i].getPosition().y > playerObject.player.getPosition().y)
				{
					playerObject.player.setPosition(playerObject.player.getPosition().x, groundList[i].getPosition().y - (playerObject.player.getSize().y - 0.1));
					playerObject.onGround = true;
				}
			}

			if (!playerObject.gameOn)
			{
				groundList.clear();
				groundList = setupStartPoint();
			}
			else
				groundList = generatePlatforms(playerObject.player, groundList, playerObject.velocityX); //generating the new ground list

			//debuging
			//cout << player.getPosition().x << " " << player.getPosition().y << endl;
			//cout << groundList[0].getPosition().x << " " << groundList[0].getPosition().y << endl;
			//cout << "onGround: " << onGround << "   " << "inAir: " << inAir << endl;
			//std::cout << groundList.size() << endl;
			//cout << scalerX << " " << scalerY << endl;
			//cout << velocityX << " " << velocityY << endl;

			//post processing
			view.setCenter(playerObject.player.getPosition().x + 110, playerObject.player.getPosition().y + 10); 		//set screen following player

			score = (playerObject.player.getPosition().x - 50) / 100;  //scoring formula
			text.setString("Score: " + to_string(score));
			text.setPosition(playerObject.player.getPosition().x - 130, playerObject.player.getPosition().y - 230);	// print score and follow the player

			window.setView(view); //set scene
			window.clear();				//clear scene

			window.draw(playerObject.player);	//set objects to be drawn
			for (int i = 0; i <= groundList.size() - 1; i++)
				window.draw(groundList[i]);
			window.draw(text);

			window.display();			//draw the scene
			clock.restart();			//restarting clock
		}
	}

	return 0;
}
