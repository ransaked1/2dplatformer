#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "2dplat.h"

//This function creates the start of the platformer with 2 inital premade platforms
std::vector<sf::RectangleShape> setupStartPoint()
{
  std::vector<sf::RectangleShape> groundList;

  sf::RectangleShape ground;			//the long ground object
	ground.setSize(sf::Vector2f(700, 30));
	ground.setPosition(0, 400);

	sf::RectangleShape ground2;			//a platform
	ground2.setSize(sf::Vector2f(200, 30));
	ground2.setPosition(850, 340);

	groundList.push_back(ground);		//putting the predefined init ground objects
	groundList.push_back(ground2);

  return groundList;
}

//This function takes a vector of rectangles and generates a new vector identical to the original
//but adds a new rendomly generated rectangle at the end
sf::RectangleShape createNewPlatform(std::vector<sf::RectangleShape> groundList, double velocityX)
{
  int dist;
  int height;
  int size = rand() % 220 + 80;
  int chance = rand() % 7 + 1;
  sf::RectangleShape tmp = groundList.back();

  //generating the random values
  if (chance == 1)
  {
    dist = 0;
    height = 0;
  }
  else
  {
    dist = rand() % ((int)velocityX * DIST_MAX_SCALE) + ((int)velocityX * DIST_MIN_SCALE);
    height = rand() % 110 - 50;
  }

  //creating the new rectangle
  sf::RectangleShape newPlatform;
  newPlatform.setSize(sf::Vector2f(size, 30));
  newPlatform.setPosition(tmp.getPosition().x + tmp.getSize().x + dist, tmp.getPosition().y - height);

  return newPlatform;
}

std::vector<sf::RectangleShape> generatePlatforms(sf::RectangleShape player, std::vector<sf::RectangleShape> groundList, double velocityX)
{
    if (player.getPosition().x > groundList[0].getPosition().x + groundList[0].getSize().x + 190)
    {
      if (groundList.size() < 4)
        groundList.push_back(createNewPlatform(groundList, velocityX));
      if (groundList.size() == 4)
        groundList.erase(groundList.begin());
    }

  return groundList;
}
