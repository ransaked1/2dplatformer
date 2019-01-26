#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "2dplat.h"

sf::RectangleShape createNewPlatform(std::vector<sf::RectangleShape> groundList, double velocityX)
{
  int dist;
  int height;
  int size = rand() % 300 + 100;
  int chance = rand() % 5 + 1;
  sf::RectangleShape tmp = groundList.back();

  if (chance == 1)
  {
    dist = 0;
    height = 0;
  }
  else
  {
    dist = rand() % ((int)velocityX * DIST_MAX_SCALE) + ((int)velocityX * DIST_MIN_SCALE);
    height = rand() % 100 + -30;
  }

  sf::RectangleShape newPlatform;
  newPlatform.setSize(sf::Vector2f(size, 30));
  newPlatform.setPosition(tmp.getPosition().x + tmp.getSize().x + dist, tmp.getPosition().y - height);

  return newPlatform;
}

std::vector<sf::RectangleShape> generatePlatforms(sf::RectangleShape player, std::vector<sf::RectangleShape> groundList, double velocityX)
{
  for (int i = 0; i <= groundList.size() - 1; i++)
  {
    if (player.getPosition().x > groundList[i].getPosition().x + groundList[i].getSize().x + 90)
    {
      groundList.erase(groundList.begin() + i);
      groundList.push_back(createNewPlatform(groundList, velocityX));
      groundList.push_back(createNewPlatform(groundList, velocityX));
    }
  }

  return groundList;
}
