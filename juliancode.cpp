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
#include "FileHelper.h"

using namespace std;

const int tile1 = (100)-1; //# of tiles
int levelWidth = 20; // # of columns
int levelHeight = 5; //# of rows

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
ground layer1[tile1+1]; //must be plus 1 of tile1

chest gold;
chest gold2;
sf::Texture HUD;
sf::Sprite HUDsprite;



sf::RenderWindow window(sf::VideoMode(600, 600), "Surface");


int main()
{
   string imagePath = FileHelper::imagePath();

    //LOADING SPRITES
    steven.loadTexture(imagePath + "SurfaceSpriteSheet1.png");
    gold.loadTexture(imagePath + "chest.png");
    gold2.loadTexture(imagePath + "chest.png");

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
    for(int x = 0; x <=tile1; x++)
    {
        layer1[x].sprite.setScale(8,8);
    }

    //POSITIONING SPRITES
    gold.sprite.setPosition(100,188);
    gold2.sprite.setPosition(100+(gold.distance*3),188);

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

    gold.hitboxes();
    gold2.hitboxes();

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
            steven.speedX = speedX;
            steven.speedY = speedY;
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

    	gold.doIntersectionCheck(steven,time);
    	gold2.doIntersectionCheck(steven,time);


    	window.clear();

        for(int x = 0; x <= tile1; x++)
        {
            window.draw(layer1[x].sprite);
        }

        if(firstTime == true)
        {
            int countplease = 0;
            firstTime == false;

            for (int r = 0; r < levelHeight; r++)
            {
                bool pleasebreak = false;
                for (int c = 0; c < levelWidth; c++)
                {
                    layer1[r*levelWidth+c].sprite.setPosition(c*128+64,r*128+300);
                    countplease++;

                    if (countplease == tile1+1) {pleasebreak = true; break;}
                }
                if (pleasebreak) break;

            }
        }

    	window.draw(steven.sprite);
        gold.draw(window);
        gold2.draw(window);


    	window.draw(HUDsprite);

    	if(firstTime2 == true)
        {
            firstTime2 = false;
            steven.sprite.setPosition(250,180);
        }

        sf::FloatRect visibleArea(steven.x-300,steven.y-300,600,600);
        HUDsprite.setPosition(steven.x-300,steven.y-300);
        window.setView(sf::View(visibleArea));
    	window.display();

	}
}

void doBoundariesStuff() {
float width = steven.texture.getSize().x; //170?
float height = steven.texture.getSize().y; //289 pixels tall? Did you scale the sprite up by 4? 56 pixels works

//player
/*
if (steven.x < steven.width*4) steven.setPosition(steven.width*4,steven.y);
if (steven.x > 600 - steven.width*4) steven.setPosition(600 - steven.width*4,steven.y);
if (steven.y > 600 - steven.height*4) steven.setPosition(steven.x,600 - steven.height*4);
*/

if (steven.y < 180) steven.setPosition(steven.x,180);

}

void doAnimationStuff(int elapsed) {
steven.updateTexture(elapsed);

}
void drawHUD()
{

}
