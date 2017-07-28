#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "player.h"
//#include "ResourcePath.hpp"

#include <windows.h>
using namespace std;
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


    player steven;

	sf::RenderWindow window(sf::VideoMode(600, 600), "Surface");
	window.setFramerateLimit(60);
	sf::Sprite sprite;
	sf::Texture texture;


	if (!texture.loadFromFile(imagePath + "gnomechild.png"))
	{
    	std::cout << "reeeeeee file path " << std::endl;
	}
	sprite.setTexture(texture);
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

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    	{
        	sprite.move(sf::Vector2f(-1*steven.base_speed * time.asMilliseconds(), 0));
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    	{
        	sprite.move(sf::Vector2f(0, -1*steven.base_speed * time.asMilliseconds()));
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    	{
        	sprite.move(sf::Vector2f(0, steven.base_speed * time.asMilliseconds()));
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    	{
        	sprite.move(sf::Vector2f(steven.base_speed * time.asMilliseconds(), 0));
    	}

    	clock.restart().asMilliseconds();

    	window.clear();

    	window.draw(sprite);

    	window.display();
cout << " x is " << sprite.getPosition().x << endl;
    	//std::cout << 1.0f / time.asSeconds() << std::endl; //Prints the frame rate to the console.

	}
}


