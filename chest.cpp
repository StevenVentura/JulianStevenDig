#include "chest.h"
#include <iostream>

using namespace std;

chest::chest()
{
    x = 0;
    y = 0;
    width = 12;
    height = 12;
    sprite.setOrigin(width/2,height/2);

    sprite.setTextureRect(sf::IntRect(0,0,width,height));
}

chest::~chest()
{

}

void chest::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;

    sprite.setPosition(x,y);
}

void chest::loadTexture(string pngPath) {

    if (!texture.loadFromFile(pngPath))
	{
    	std::cout << "reeeeeee file path " << std::endl;
	}
	sprite.setTexture(texture);
}
