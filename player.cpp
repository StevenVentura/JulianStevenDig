#include "player.h"
#include <iostream>
using namespace std;

player::player() {
x = 0;
y = 0;

}
player::~player() {
}

void player::setPosition(float x, float y) {
this->x = x;
this->y = y;

sprite.setPosition(x,y);

}


void player::loadTexture(string pngPath) {

    if (!texture.loadFromFile(pngPath))
	{
    	std::cout << "reeeeeee file path " << std::endl;
	}
	sprite.setTexture(texture);

	}

void player::pls() {
x = x + 1;

}
