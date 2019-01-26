#ifndef PLAT_H
# define PLAT_H

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#define GRAVITY 0.85   //global initial gravity
#define DIST_MAX_SCALE 30
#define DIST_MIN_SCALE 20

void	applyPhysics(sf::RectangleShape *player, double *velocityY, bool *onGround,
  bool *inAir, double gravity, double velocityX, float scalerY, bool *gameOn);

std::vector<sf::RectangleShape> generatePlatforms(sf::RectangleShape player, std::vector<sf::RectangleShape> groundList,
  double velocityX);

#endif
