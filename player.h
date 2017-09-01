#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include <string>
using namespace std;
class player {
 public:
player();
~player();

void pls();
void loadTexture(string imagePath);
void updateTexture(int elapsed);
void setPosition(float x, float y);
void setFacing(int direction);
void snapX();
void snapY();

sf::Sprite sprite;
sf::Texture texture;
float x, y, lx, ly;
float width,height;
int spriteCycleSpeed;
int spriteCycleCounter;
int currentSprite;
int facingDirection;

int recenter = true;
int recenter2 = true;

bool facingLeft;
bool pointedUpLast;
float speedX, speedY;

const static float base_speed = 0.25;

};
#endif
