#include "ground.h"
#include <iostream>

using namespace std;

ground::ground()
{
    x = 300;
    y = 300;
    width = 16;
    height = 16;
    sprite.setOrigin(width/2,height/2);
}

ground::~ground() {
}

void ground::setPosition(float x, float y) {
this->x = x;
this->y = y;

sprite.setPosition(x,y);
}

void ground::loadTexture(string pngPath) {

    if (!texture.loadFromFile(pngPath))
	{
    	std::cout << "reeeeeee file path " << std::endl;
	}
	sprite.setTexture(texture);


}
