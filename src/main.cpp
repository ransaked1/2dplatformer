#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;

/*TO DO!
-put everything physics related in applyPhysics
-learn level building or generate procedualy
-prepare everything for pluging in AI
-create a ground class?
*/

void	applyPhysics(sf::RectangleShape *player, sf::RectangleShape *ground, double *velocityY)
{

}

int main()
{
	/************************\
	|*** INITIALIZATIONS ****|
	\************************/

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(720, 720), "SFML 2D Platformer!");	//initializing window
	sf::View view(sf::FloatRect(50.f, 100.f, 500.f, 500.f));

	sf::RectangleShape player;			//creating the controllable shape
	player.setSize(sf::Vector2f(50, 25));
	player.setPosition(50, 300);

	sf::RectangleShape ground;			//the lomng ground object
	ground.setSize(sf::Vector2f(1000, 30));
	ground.setPosition(0, 400);

	sf::RectangleShape ground2;			//a platform
	ground2.setSize(sf::Vector2f(150, 30));
	ground2.setPosition(200, 340);

	bool onGround;								//Is the player on the ground?
	bool inAir;										//Is the player going against the gravity?

	const double gravity = 1.6;   //global gravity always positive nr (going down)
	double velocityX = 0;					//player velocity in X direction
	double velocityY = 0;					//player velocity in Y direction

	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");		//scoring text
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(25);

	int score = 0;


	while (window.isOpen())		//infinite loop while window is opens
	{
		sf::Event event;

		//If the object is accelerating upward and is not on the ground then it's in the air
		if (velocityY < 0 && onGround == false)
			inAir = true;
		else
			inAir = false;

		//Checking if player is intersection a ground object and testing if its over the ground
		if ((player.getGlobalBounds().intersects(ground.getGlobalBounds()) && ground.getPosition().y - 20 >= player.getPosition().y) ||
		(player.getGlobalBounds().intersects(ground2.getGlobalBounds()) && ground2.getPosition().y - 20 >= player.getPosition().y))
				onGround = true;
		else
			onGround = false;

		while (window.pollEvent(event)) //checking if there is any event before updating the frame
		{
			switch (event.type)
			{
				case sf::Event::Closed: //if window is getting closed
					window.close();
					break;

				default: //if none of the above
					break;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && onGround == true) //can jump only once when on the ground
			{
					velocityY = -20;
					onGround = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))    // left and right movement
				velocityX = 1.3;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				velocityX = -1.3;
			else
				velocityX = 0;
		}

		if (onGround == false ||  inAir == true)   //if object is not on the ground or in the air apply gravity
		{
			player.move(velocityX, velocityY);

			velocityY += gravity;					//gravity decelerating velocityY
			if(velocityY > gravity * 2)   //terminal velocity = is gravity x constant
				velocityY = gravity * 2;
		}
		else
			player.move(velocityX, 0);		//if no change in Y move on X axis

		if (player.getPosition().y > 440) //reset player after dying
			player.setPosition(50, 300);

		//cout << player.getPosition().x << " " << player.getPosition().y << endl;
		//cout << ground2.getPosition().x << " " << ground2.getPosition().y << endl;

		cout << "onGround: " << onGround << "   " << "inAir: " << inAir << endl; //debuging

		view.setCenter(player.getPosition().x + 80, player.getPosition().y - 80); //set screen following player

		score = (player.getPosition().x - 50) / 100;  //scoring formula
		text.setString("Score: " + to_string(score));
		text.setPosition(player.getPosition().x - 120, player.getPosition().y - 300); // print score and follow the player

		window.setView(view); //set scene
		window.clear();				//clear scene

		window.draw(player);		//set objects to be drawn
		window.draw(ground);
		window.draw(ground2);
		window.draw(text);

		window.display();			//draw the scene
	}

	return 0;
}
