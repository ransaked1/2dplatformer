#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "2dplat.h"

void	applyPhysics(playerObject *playerObject)
{
	//if object is not on the ground or in the air apply gravity
	if (playerObject->onGround == false || playerObject->inAir == true)
	{
		playerObject->player.move(playerObject->velocityX, playerObject->velocityY);

		playerObject->velocityY += playerObject->gravity;					//gravity decelerating velocityY
		if(playerObject->velocityY > 10 * playerObject->gravity)   //set terminal speed for fall
			playerObject->velocityY = 10 * playerObject->gravity;
	}
	else
		playerObject->player.move(playerObject->velocityX, 0);		//if no change in Y move on X axis

	//reset player after falling off
	if (playerObject->player.getPosition().y > 1000)
  {
		playerObject->player.setPosition(50, 390);
    playerObject->gameOn = false;
  }

	//If the object is accelerating upward and is not on the ground then it's in the air
	if (playerObject->velocityY < 0 && playerObject->onGround == false)
		playerObject->inAir = true;
	else
		playerObject->inAir = false;

}
