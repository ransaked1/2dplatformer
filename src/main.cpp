#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;

/*TO DO!
-put everything physics related in applyPhysics
-learn level building or generate randomly
-prepare input for pluging in AI
-create a ground class and objects?
*/

void	applyPhysics(sf::RectangleShape *player, sf::RectangleShape *ground, double *velocityY)
{

}

int main()
{
	/***********************\
	**** INITIALIZATIONS ****
	\***********************/

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(720, 720), "SFML 2D Platformer!");	//initializing window size and name
	sf::View view(sf::FloatRect(50.f, 100.f, 500.f, 500.f));                  //initializing the field of view

	sf::RectangleShape player;			//creating the controllable shape
	player.setSize(sf::Vector2f(50, 25));
	player.setPosition(50, 300);
	player.setFillColor(sf::Color::Red);

	sf::RectangleShape ground;			//the long ground object
	ground.setSize(sf::Vector2f(1000, 30));
	ground.setPosition(0, 400);

	sf::RectangleShape ground2;			//a platform
	ground2.setSize(sf::Vector2f(150, 30));
	ground2.setPosition(200, 340);

	bool onGround;								//Is the player on the ground?
	bool inAir;										//Is the player going against the gravity?

	const double gravity = 2.7;   //global gravity always positive nr (going down)
	double velocityX = 0;					//player velocity in X direction
	double velocityY = 0;					//player velocity in Y direction

	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");		//scoring text setup
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(25);

	int score = 0;

	//infinite loop while window is open
	while (window.isOpen())
	{
		sf::Event event;	//event is a buffer checking key states

		//checking if there is any button pressed before updating the frame
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed: //if window is getting closed
					window.close();
					break;

				default: //if none of the above
					break;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				break;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && onGround == true) //can jump only once when on the ground
			{
					velocityY = -30;
					onGround = false;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))    // left and right movement
				velocityX = 6;
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
				velocityX = -6;
			else
				velocityX = 0;
		}
		
		//Code to be put in applyPhysics (without breaking everything!)

	//-----------------------------------------\\
		//applying physics
		if (onGround == false || inAir == true)   //if object is not on the ground or in the air apply gravity
		{
			player.move(velocityX, velocityY);

			velocityY += gravity;					//gravity decelerating velocityY
			if(velocityY > gravity  )   //terminal velocity = is gravity x constant
				velocityY = gravity ;
		}
		else
			player.move(velocityX, 0);		//if no change in Y move on X axis

		//reset player after falling off (bellow pixel 440 from top)
		if (player.getPosition().y > 440)
			player.setPosition(50, 300);

		//If the object is accelerating upward and is not on the ground then it's in the air
		if (velocityY < 0 && onGround == false)
			inAir = true;
		else
			inAir = false;

		//Checking if player is intersection a ground object and verifying if its over the ground
		if (player.getGlobalBounds().intersects(ground.getGlobalBounds()) && ground.getPosition().y - (player.getSize().y - 0.1) < player.getPosition().y && ground.getPosition().y - 22  > player.getPosition().y)
		{
			player.setPosition(player.getPosition().x, ground.getPosition().y - (player.getSize().y - 0.1));
			onGround = true;
		}
		else if (player.getGlobalBounds().intersects(ground2.getGlobalBounds()) && ground2.getPosition().y - (player.getSize().y - 0.1) < player.getPosition().y && ground2.getPosition().y - 22 > player.getPosition().y)
		{
			player.setPosition(player.getPosition().x, ground2.getPosition().y - (player.getSize().y - 0.1));
			onGround = true;
		}
		else
			onGround = false;
	//------------------------------------------------\\

		//debuging
		cout << player.getPosition().x << " " << player.getPosition().y << endl;
		//cout << ground2.getPosition().x << " " << ground2.getPosition().y << endl;
		cout << "onGround: " << onGround << "   " << "inAir: " << inAir << endl;

		//post processing
		view.setCenter(player.getPosition().x + 80, player.getPosition().y - 80); 		//set screen following player

		score = (player.getPosition().x - 50) / 100;  //scoring formula
		text.setString("Score: " + to_string(score));
		text.setPosition(player.getPosition().x - 120, player.getPosition().y - 300);	// print score and follow the player

		window.setView(view); //set scene
		window.clear();				//clear scene

		window.draw(player);	//set objects to be drawn
		window.draw(ground);
		window.draw(ground2);
		window.draw(text);

		window.display();			//draw the scene
	}
	return 0;
}
