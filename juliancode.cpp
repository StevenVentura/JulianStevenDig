#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "player.h"
#include "ground.h"
#include "chest.h"
#include "Direction.h"
//#include "ResourcePath.hpp"

#include <windows.h>
using namespace std;

int tile1 = 14; //if tile1 = 0, then 1 tile will be created. If tile1 = 1, then 2 tiles will be created. Every 5 tiles a new row is created.

void doBoundariesStuff();
void doAnimationStuff(int);
void drawHUD();
bool firstTime = true;
bool firstTime2 = true;

//CREATING OBJECTS
player steven;
ground layer1[15]; //must be plus 1 of tile1
chest gold;
sf::Texture HUD;
sf::Sprite HUDsprite;

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


    //LOADING SPRITES
    steven.loadTexture(imagePath + "SurfaceSpriteSheet1.png");
    gold.loadTexture(imagePath + "chest.png");
    //load hud
    if (!HUD.loadFromFile(imagePath + "HUD.png")){
        cout << "reeeeeeeeeeeeeeeeeeeee" << endl;
    }

    HUDsprite.setTexture(HUD);

    HUDsprite.scale(600.0/HUD.getSize().x,600.0/HUD.getSize().x);

    for(int x = 0; x <= tile1; x++)
    {
        layer1[x].loadTexture(imagePath + "ground.png");
    }


    //UPDATING SPRITES
    steven.updateTexture(10000);

    //SCALING SPRITES
    steven.sprite.setScale(8,8);
    gold.sprite.setScale(8,8);
    for(int x = 0; x <=tile1; x++)
    {
        layer1[x].sprite.setScale(8,8);
    }

	sf::RenderWindow window(sf::VideoMode(600, 600), "Surface");
	window.setFramerateLimit(60);

	sf::Clock clock;
	bool firsttime = true;

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
        	steven.setFacing(Direction::WEST);
    	}
    	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    	{
        	steven.sprite.move(sf::Vector2f(0, -1*steven.base_speed * time.asMilliseconds()));
        	steven.setFacing(Direction::NORTH);
    	}
    	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    	{
        	steven.sprite.move(sf::Vector2f(0, steven.base_speed * time.asMilliseconds()));
        	steven.setFacing(Direction::SOUTH);
    	}
    	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    	{
        	steven.sprite.move(sf::Vector2f(steven.base_speed * time.asMilliseconds(), 0));
        	steven.setFacing(Direction::EAST);
    	}

    	//update his position variables
    	steven.x = steven.sprite.getPosition().x;
    	steven.y = steven.sprite.getPosition().y;

    	doBoundariesStuff();
    	doAnimationStuff(time.asMilliseconds());

    	clock.restart().asMilliseconds();

    	if(steven.sprite.getGlobalBounds().intersects(gold.sprite.getGlobalBounds()))
        {
            if(steven.facingDirection == Direction::EAST)
            {
                steven.sprite.move(sf::Vector2f(-1*steven.base_speed * time.asMilliseconds(), 0));
            }
            if(steven.facingDirection == Direction::WEST)
            {
                steven.sprite.move(sf::Vector2f(steven.base_speed * time.asMilliseconds(), 0));
            }
            if(steven.facingDirection == Direction::NORTH)
            {
                steven.sprite.move(sf::Vector2f(0, steven.base_speed * time.asMilliseconds()));
            }
            if(steven.facingDirection == Direction::SOUTH)
            {
                steven.sprite.move(sf::Vector2f(0, -1*steven.base_speed * time.asMilliseconds()));
            }
            std::cout << "The sprite has collided" << std:: endl;
        }

    	window.clear();

        for(int x = 0; x <= tile1; x++)
        {
            window.draw(layer1[x].sprite);
        }

        if(firstTime == true)
        {
            firstTime == false;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 5; c++)
                {
                    layer1[r*5+c].sprite.setPosition(c*128+64,r*128+300);
                }

            }
        }

    	window.draw(steven.sprite);

    	window.draw(gold.sprite);

    	gold.sprite.setPosition(300,188);

    	window.draw(HUDsprite);

    	if(firstTime2 == true)
        {
            firstTime2 = false;
            steven.sprite.setPosition(100,180);
        }

        if(steven.sprite.getGlobalBounds().intersects(layer1[0].sprite.getGlobalBounds()))
        {

        }

    	window.display();

	}
}

void doBoundariesStuff() {
float width = steven.texture.getSize().x; //170?
float height = steven.texture.getSize().y; //289 pixels tall? Did you scale the sprite up by 4? 56 pixels works

//player
if (steven.x < steven.width*4) steven.setPosition(steven.width*4,steven.y);
if (steven.x > 600 - steven.width*4) steven.setPosition(600 - steven.width*4,steven.y);
if (steven.y < steven.height*4) steven.setPosition(steven.x,steven.height*4);
if (steven.y > 600 - steven.height*4) steven.setPosition(steven.x,600 - steven.height*4);

}

void doAnimationStuff(int elapsed) {
steven.updateTexture(elapsed);

}
void drawHUD()
{

}
