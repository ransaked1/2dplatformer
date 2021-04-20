#ifndef PLAT_H
# define PLAT_H

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#define GRAVITY 0.82   //global gravity
#define DIST_MAX_SCALE 28
#define DIST_MIN_SCALE 26

class playerObject{
  public:
    sf::RectangleShape player;
    double velocityY;
    double velocityX;
    bool onGround;
    bool inAir;
    bool gameOn;
    float scalerY;
    double gravity;

    playerObject() {
      player.setSize(sf::Vector2f(50, 25));
      player.setPosition(50, 390);
      player.setFillColor(sf::Color::Red);

      velocityY = 0;
      velocityX = 4.5;

      gameOn = false;

      scalerY = 1.0;
    }

    void setGravity() {
      gravity = GRAVITY * scalerY;
    }
};

void	applyPhysics(playerObject *playerObject);

std::vector<sf::RectangleShape> generatePlatforms(sf::RectangleShape player, std::vector<sf::RectangleShape> groundList,
  double velocityX);

std::vector<sf::RectangleShape> setupStartPoint();

#endif
