#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "2dplat.h"

void	applyPhysics(sf::RectangleShape *player, double *velocityY, bool *onGround, bool *inAir, double gravity, double velocityX, float scalerY, bool *gameOn)
{
	//if object is not on the ground or in the air apply gravity
	if (*onGround == false || *inAir == true)
	{
		player->move(velocityX, *velocityY);

		*velocityY += gravity;					//gravity decelerating velocityY
		if(*velocityY > 10 * gravity)
			*velocityY = 10 * gravity;
	}
	else
		player->move(velocityX, 0);		//if no change in Y move on X axis

	//reset player after falling off
	if (player->getPosition().y > 2500)
  {
		player->setPosition(50, 390);
    *gameOn = false;
  }

	//If the object is accelerating upward and is not on the ground then it's in the air
	if (*velocityY < 0 && *onGround == false)
		*inAir = true;
	else
		*inAir = false;

}
