#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
//#include "ResourcePath.hpp"


int main()
{
    std::string resourcePath = "C:\\Users\\8stev\\Desktop\\NewCode\\JulianStevenDig\\images\\";
	sf::RenderWindow window(sf::VideoMode(600, 600), "Surface");

	window.setFramerateLimit(60);

	sf::Sprite sprite;

	sf::Texture texture;

	if (!texture.loadFromFile(resourcePath + "gnomechild.png"))
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
        	sprite.move(sf::Vector2f(-0.5 * time.asMilliseconds(), 0));
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    	{
        	sprite.move(sf::Vector2f(0, -0.5 * time.asMilliseconds()));
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    	{
        	sprite.move(sf::Vector2f(0, 0.5 * time.asMilliseconds()));
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    	{
        	sprite.move(sf::Vector2f(0.5 * time.asMilliseconds(), 0));
    	}

    	clock.restart().asMilliseconds();

    	window.clear();

    	window.draw(sprite);

    	window.display();

    	std::cout << 1.0f / time.asSeconds() << std::endl; //Prints the frame rate to the console.
	}
}


