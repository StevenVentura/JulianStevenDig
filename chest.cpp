#include "chest.h"
#include "FileHelper.h"
#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

chest::chest()
{
    x = 0;
    y = 0;
    width = 12;
    height = 12;
    sprite.setOrigin(width/2,height/2);
    distance = 106;

    sprite.setTextureRect(sf::IntRect(0,0,width,height));
}

chest::~chest()
{

}
void chest::doIntersectionCheck(player& steven,sf::Time& time) {

float please = 1.0f;

if(steven.sprite.getGlobalBounds().intersects(rectangle.getGlobalBounds()) && steven.y > rectangle.getGlobalBounds().top) //pushes down
        {

                steven.sprite.setPosition(steven.x,rectangle.getGlobalBounds().top+rectangle.getGlobalBounds().height+steven.height/2);
        }

        if(steven.sprite.getGlobalBounds().intersects(rectangle2.getGlobalBounds()) && steven.y < rectangle2.getGlobalBounds().top) //pushes up
        {
            steven.sprite.setPosition(steven.x,rectangle2.getGlobalBounds().top-steven.height/2);

        }

        if(steven.sprite.getGlobalBounds().intersects(rectangle3.getGlobalBounds()) && steven.x < rectangle3.getGlobalBounds().left) //pushes left
        {
            steven.sprite.setPosition(rectangle3.getGlobalBounds().left-steven.width/2,steven.y);

        }

        if(steven.sprite.getGlobalBounds().intersects(rectangle4.getGlobalBounds())  && steven.x > rectangle3.getGlobalBounds().left) //pushes right
        {
            steven.sprite.setPosition(rectangle4.getGlobalBounds().left+rectangle4.getGlobalBounds().width+steven.width/2,steven.y);
        }


}

void chest::draw(sf::RenderWindow& window) {
window.draw(sprite);
    window.draw(rectangle);
    window.draw(rectangle2);
    window.draw(rectangle3);
    window.draw(rectangle4);
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

void chest::hitboxes()
{
    //sprite.setScale(8,8);
    loadTexture(FileHelper::imagePath() + "chest.png");

    rectangle.setSize(sf::Vector2f(16, 4));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOrigin(16/2,4/2);
    rectangle.setPosition(sprite.getPosition().x,sprite.getPosition().y+7);

    rectangle2.setSize(sf::Vector2f(16, 4));
    rectangle2.setFillColor(sf::Color::Transparent);
    rectangle2.setOrigin(16/2,4/2);
    rectangle2.setPosition(sprite.getPosition().x,sprite.getPosition().y-7);

    rectangle3.setSize(sf::Vector2f(16, 4));
    rectangle3.setFillColor(sf::Color::Transparent);
    rectangle3.setOrigin(16/2,4/2);
    rectangle3.setPosition(sprite.getPosition().x-8,sprite.getPosition().y);
    rectangle3.setRotation(90);

    rectangle4.setSize(sf::Vector2f(16, 4));
    rectangle4.setFillColor(sf::Color::Transparent);
    rectangle4.setOrigin(16/2,4/2);
    rectangle4.setPosition(sprite.getPosition().x+8,sprite.getPosition().y);
    rectangle4.setRotation(90);
}
