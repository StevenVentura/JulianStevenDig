#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "player.h"
#include "ground.h"
//#include "ResourcePath.hpp"

#include <windows.h>
using namespace std;


void doBoundariesStuff();
void doAnimationStuff(int);
player steven;
ground layer1;


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

    layer1.loadTexture(imagePath + "ground.png");
    layer1.sprite.setScale(8,8);

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

    	window.draw(layer1.sprite);
    	window.draw(steven.sprite);

    	layer1.sprite.setPosition(300,300);

    	window.display();

	}
}

void doBoundariesStuff() {
float width = steven.texture.getSize().x; //170?
float height = steven.texture.getSize().y; //289 pixels tall? Did you scale the sprite up by 4? 56 pixels works

std::cout << width << endl;

//player
if (steven.x < steven.width*4) steven.setPosition(steven.width*4,steven.y);
if (steven.x > 600 - steven.width*4) steven.setPosition(600 - steven.width*4,steven.y);
if (steven.y < steven.height*4) steven.setPosition(steven.x,steven.height*4);
if (steven.y > 600 - steven.height*4) steven.setPosition(steven.x,600 - steven.height*4);



}

void doAnimationStuff(int elapsed) {
steven.updateTexture(elapsed);

}


