#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "2dplat.h"

//This function takes a vector of rectangles and generates a new vwector identical to the original
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
    height = rand() % 110 + -50;
  }

  //creating the new rectangle
  sf::RectangleShape newPlatform;
  newPlatform.setSize(sf::Vector2f(size, 30));
  newPlatform.setPosition(tmp.getPosition().x + tmp.getSize().x + dist, tmp.getPosition().y - height);

  return newPlatform;
}

//This function takes the vector of triangles and the player. It removes all the rectangles
//behind the player and adds two new rectangles in front
std::vector<sf::RectangleShape> generatePlatforms(sf::RectangleShape player, std::vector<sf::RectangleShape> groundList, double velocityX)
{
  for (int i = 0; i <= groundList.size() - 1; i++)
  {
    if (player.getPosition().x > groundList[i].getPosition().x + groundList[i].getSize().x + 90)
    {
      groundList.erase(groundList.begin() + i);                         //erasing rectangle if behind
      groundList.push_back(createNewPlatform(groundList, velocityX));   //add a rectangle in front
      groundList.push_back(createNewPlatform(groundList, velocityX));   //add the second rectangle in front
    }
  }

  return groundList;
}
