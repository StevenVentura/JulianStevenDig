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

sf::Sprite sprite;
sf::Texture texture;
float x, y, lx, ly;
float width,height;
int spriteCycleSpeed;
int spriteCycleCounter;
int currentSprite;
int facingDirection;
bool facingLeft;
float speedX, speedY;

const static float base_speed = 0.25;

};
#endif
