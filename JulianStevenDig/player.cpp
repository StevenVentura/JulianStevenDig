#include "player.h"
#include "Direction.h"
#include <iostream>
using namespace std;

player::player() {
x = 0;
y = 0;
width=13;
height=14;
currentSprite = 0;
spriteCycleCounter = 0;
spriteCycleSpeed = 200;//milliseconds
facingDirection = Direction::EAST;
facingLeft = false;

sprite.setOrigin(width/2,height/2);

}
player::~player() {
}

void player::setPosition(float x, float y) {
this->x = x;
this->y = y;


sprite.setPosition(x,y);

}

void player::setFacing(int direction) {

if ((facingLeft == false && direction == Direction::WEST) || (facingLeft == true && direction == Direction::EAST)) {
    sprite.scale(-1,1);
    facingLeft = (direction == Direction::WEST);
}

int please = 1;
if (facingLeft)
    please = -1;

if (direction == Direction::NORTH)
    sprite.setRotation(-90*please);

else if (direction == Direction::SOUTH)
    sprite.setRotation(90*please);
    else sprite.setRotation(0);

facingDirection = direction;
}

void player::loadTexture(string pngPath) {

    if (!texture.loadFromFile(pngPath))
	{
    	std::cout << "reeeeeee file path " << std::endl;
	}
	sprite.setTexture(texture);


	}

void player::updateTexture(int elapsed) {
spriteCycleCounter += elapsed;

if (spriteCycleCounter > spriteCycleSpeed) {
    spriteCycleCounter = 0;
    //go to the next sprite in the cycle
    currentSprite++;
    if (currentSprite >= 2) currentSprite = 0;

    //now draw the new sprite
    switch(currentSprite) {
case 0:
sprite.setTextureRect(sf::IntRect(7,8,width,height));
break;
case 1:
sprite.setTextureRect(sf::IntRect(26,8,width,height));
break;


    }

}

}

void player::pls() {
x = x + 1;

}
