#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <cmath>
#include <windows.h>
#include <iostream>
#include <string>

#include "player.h"
#include "ground.h"
#include "chest.h"
#include "Direction.h"

using namespace std;

int tile1 = 14; //if tile1 = 0, then 1 tile will be created. If tile1 = 1, then 2 tiles will be created. Every 5 tiles a new row is created.

void doBoundariesStuff();
void doAnimationStuff(int);
void drawHUD();
bool firstTime = true;
bool firstTime2 = true;

int gridSize = 8;
float moveSpeed = 1;
bool isMoving = false;
int moveTimer = 0;
int speedX = 0;
int speedY = 0;
float x = 0;
float y = 0;

//CREATING OBJECTS
player steven;
ground layer1[15]; //must be plus 1 of tile1
chest gold;
sf::Texture HUD;
sf::Sprite HUDsprite;
sf::RectangleShape rectangle;
sf::RectangleShape rectangle2;
sf::RectangleShape rectangle3;
sf::RectangleShape rectangle4;

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

	sf::Music music;

	if(!music.openFromFile(imagePath + "edgy.ogg"))
    {
        std::cout << "reeeee" << std::endl;
    }

    music.play();
    music.setVolume(20);

    rectangle.setSize(sf::Vector2f(96, 10));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOrigin(96/2,10/2);
    rectangle.setPosition(300,231);

    rectangle2.setSize(sf::Vector2f(96, 10));
    rectangle2.setFillColor(sf::Color::Transparent);
    rectangle2.setOrigin(96/2,10/2);
    rectangle2.setPosition(300,145);

    rectangle3.setSize(sf::Vector2f(96, 10));
    rectangle3.setFillColor(sf::Color::Transparent);
    rectangle3.setOrigin(96/2,10/2);
    rectangle3.setPosition(252,188);
    rectangle3.setRotation(90);

    rectangle4.setSize(sf::Vector2f(96, 10));
    rectangle4.setFillColor(sf::Color::Transparent);
    rectangle4.setOrigin(96/2,10/2);
    rectangle4.setPosition(348,188);
    rectangle4.setRotation(90);

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

    	if (isMoving == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                isMoving = true;
                moveTimer = gridSize;
                speedX = moveSpeed;
                speedY = 0;
                steven.setFacing(Direction::EAST);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                isMoving = true;
                moveTimer = gridSize;
                speedX = -moveSpeed;
                speedY = 0;
                steven.setFacing(Direction::WEST);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                isMoving = true;
                moveTimer = gridSize;
                speedX = 0;
                speedY = -moveSpeed;
                steven.setFacing(Direction::NORTH);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                isMoving = true;
                moveTimer = gridSize;
                speedX = 0;
                speedY = moveSpeed;
                steven.setFacing(Direction::SOUTH);
            }
        }

        if(isMoving == true)
        {
            x = speedX;
            y = speedY;
            steven.sprite.move(sf::Vector2f(x/3 * time.asMilliseconds(), y/3 * time.asMilliseconds()));
            moveTimer -= moveSpeed;
            if(moveTimer == 0) isMoving = false;
        }

    	//update his position variables
    	steven.x = steven.sprite.getPosition().x;
    	steven.y = steven.sprite.getPosition().y;
    	gold.x = gold.sprite.getPosition().x;
    	gold.y = gold.sprite.getPosition().y;

    	doBoundariesStuff();
    	doAnimationStuff(time.asMilliseconds());

    	clock.restart().asMilliseconds();

    	if(steven.sprite.getGlobalBounds().intersects(rectangle.getGlobalBounds())) //pushes down
        {
                if(x == 0)
                {
                    steven.sprite.move(sf::Vector2f(0, (abs(y/3)) * time.asMilliseconds()));
                }
                else if(y == 0)
                {
                     steven.sprite.move(sf::Vector2f(0, (abs(x/3)) * time.asMilliseconds()));
                }
        }

        if(steven.sprite.getGlobalBounds().intersects(rectangle2.getGlobalBounds())) //pushes up
        {
            if(x == 0)
                {
                    steven.sprite.move(sf::Vector2f(0, (abs(y/3))*-1 * time.asMilliseconds()));
                }
            else if(y == 0)
                {
                    steven.sprite.move(sf::Vector2f(0, (abs(x/3))*-1 * time.asMilliseconds()));
                }

        }

        if(steven.sprite.getGlobalBounds().intersects(rectangle3.getGlobalBounds())) //pushes left
        {
            if(x == 0)
                {
                    steven.sprite.move(sf::Vector2f((abs(y/3))*-1 * time.asMilliseconds(), 0));
                }
            else if(y == 0)
                {
                    steven.sprite.move(sf::Vector2f((abs(x/3))*-1 * time.asMilliseconds(), 0));
                }
        }

        if(steven.sprite.getGlobalBounds().intersects(rectangle4.getGlobalBounds())) //pushes right
        {
            if(x == 0)
                {
                    steven.sprite.move(sf::Vector2f(abs(-y/3) * time.asMilliseconds(), 0));
                }
            else if(y == 0)
                {
                    steven.sprite.move(sf::Vector2f(abs(-x/3) * time.asMilliseconds(), 0));
                }
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
        window.draw(rectangle);
        window.draw(rectangle2);
        window.draw(rectangle3);
        window.draw(rectangle4);
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
