#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "player.h"
//#include "ResourcePath.hpp"

#include <windows.h>
using namespace std;


void doBoundariesStuff();
void doAnimationStuff(int);
player steven;


std::string getexepath()
{
  char result[ MAX_PATH ];
  return std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
}



int main()
{
string imagePath = getexepath();
    imagePath = imagePath.substr(0,imagePath.find_last_of("\\"));
    imagePath = imagePath.substr(0,imagePath.find_last_of("\\"));
    imagePath = imagePath.substr(0,imagePath.find_last_of("\\"));
    imagePath = imagePath + "\\images\\";

    steven.loadTexture(imagePath + "SurfaceSpriteSheet1.png");
    steven.updateTexture(10000);
    steven.sprite.setScale(8,8);


	sf::RenderWindow window(sf::VideoMode(600, 600), "Surface");
	window.setFramerateLimit(60);

	sf::Clock clock;

	while (window.isOpen())
	{
    	sf::Event event;

    	while (window.pollEvent(event))
    	{
        	if (event.type == sf::Event::Closed)
            	window.close();
    	}

    	sf::Time time = clock.getElapsedTime();

    	steven.lx = steven.x;
    	steven.ly = steven.y;

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    	{
        	steven.sprite.move(sf::Vector2f(-1*steven.base_speed * time.asMilliseconds(), 0));
        	steven.setFacing(true);
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    	{
        	steven.sprite.move(sf::Vector2f(0, -1*steven.base_speed * time.asMilliseconds()));
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    	{
        	steven.sprite.move(sf::Vector2f(0, steven.base_speed * time.asMilliseconds()));
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    	{
        	steven.sprite.move(sf::Vector2f(steven.base_speed * time.asMilliseconds(), 0));
        	steven.setFacing(false);
    	}

    	//update his position variables
    	steven.x = steven.sprite.getPosition().x;
    	steven.y = steven.sprite.getPosition().y;

    	doBoundariesStuff();
    	doAnimationStuff(time.asMilliseconds());

    	clock.restart().asMilliseconds();

    	window.clear();

    	window.draw(steven.sprite);

    	window.display();


	}
}

void doBoundariesStuff() {
float width = steven.texture.getSize().x;
float height = steven.texture.getSize().y;

//player
if (steven.x < 0) steven.setPosition(0,steven.y);
if (steven.x > 600 - width) steven.setPosition(600 - width,steven.y);
if (steven.y < 0) steven.setPosition(steven.x,0);
if (steven.y > 600 - height) steven.setPosition(steven.x,600 - height);



}

void doAnimationStuff(int elapsed) {
steven.updateTexture(elapsed);

}


