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

float please = 0.25f;

if(steven.sprite.getGlobalBounds().intersects(rectangle.getGlobalBounds())) //pushes down
        {

                if(steven.speedX == 0)
                {
                    steven.sprite.move(sf::Vector2f(0, please*(abs(steven.speedY/3)) * time.asMilliseconds()));
                }
                else if(steven.speedY == 0)
                {
                     steven.sprite.move(sf::Vector2f(0, please*(abs(steven.speedX/3)) * time.asMilliseconds()));
                }
        }

        if(steven.sprite.getGlobalBounds().intersects(rectangle2.getGlobalBounds())) //pushes up
        {
            if(steven.speedX == 0)
                {
                    steven.sprite.move(sf::Vector2f(0, please*(abs(steven.speedY/3))*-1 * time.asMilliseconds()));
                }
            else if(steven.speedY == 0)
                {
                    steven.sprite.move(sf::Vector2f(0, please*(abs(steven.speedX/3))*-1 * time.asMilliseconds()));
                }

        }

        if(steven.sprite.getGlobalBounds().intersects(rectangle3.getGlobalBounds())) //pushes left
        {

            if(steven.speedX == 0)
                {
                    steven.sprite.move(sf::Vector2f(please*(abs(steven.speedY/3))*-1 * time.asMilliseconds(), 0));
                }
            else if(steven.speedY == 0)
                {
                    steven.sprite.move(sf::Vector2f(please*(abs(steven.speedX/3))*-1 * time.asMilliseconds(), 0));
                }
        }

        if(steven.sprite.getGlobalBounds().intersects(rectangle4.getGlobalBounds())) //pushes right
        {
            if(steven.speedX == 0)
                {
                    steven.sprite.move(sf::Vector2f(please*abs(-steven.speedY/3) * time.asMilliseconds(), 0));
                }
            else if(steven.speedY == 0)
                {
                    steven.sprite.move(sf::Vector2f(please*abs(-steven.speedX/3) * time.asMilliseconds(), 0));
                }
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
