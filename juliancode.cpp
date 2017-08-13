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


void doBoundariesStuff();
void doAnimationStuff(int);
void drawHUD();
float boolpol(bool);



float moveSpeed = 1;


float speedX = 0;
float speedY = 0;


//CREATING OBJECTS
player steven;
const int mapRows = 16, mapCols = 16;
ground layer1[mapRows][mapCols]; //must be plus 1 of tile1

chest gold;
chest gold2;
sf::Texture HUD;
sf::Sprite HUDsprite;



sf::RenderWindow window(sf::VideoMode(160*6, 144*6), "Surface"); //144

const float three = 144/2*6;
const float six = 160*6;


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
    //HUDsprite.scale(six/HUD.getSize().x,six/HUD.getSize().x);

    for (int r = 0; r < mapRows; r++)
        for (int c = 0; c < mapCols; c++)
            layer1[r][c].loadTexture(imagePath + "ground.png");


    //UPDATING SPRITES
    steven.updateTexture(10000);


    //POSITIONING SPRITES
    gold.sprite.setPosition(0+8,0+8);
    gold2.sprite.setPosition(0+8,16+8);
    steven.sprite.setPosition(32+8,32+8);
    for (int r = 0; r < mapRows; r++)
            for (int c = 0; c < mapCols; c++)
                layer1[r][c].sprite.setPosition(c*16+8,r*16+8+32);

	window.setFramerateLimit(60);

	sf::Clock clock;
	bool firsttime = true;

	/*sf::Music music;

	if(!music.openFromFile(imagePath + "edgy.ogg"))
    {
        std::cout << "reeeee" << std::endl;
    }

    music.play();
    music.setVolume(20);
*/
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

    	steven.speedX = 0; steven.speedY = 0;

    	//get da keyboard presses
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {

                steven.speedY = boolpol(steven.pointedUpLast==false) * moveSpeed * 2;
                steven.snapY();

                steven.speedX = moveSpeed;

                steven.setFacing(Direction::EAST);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {

                 steven.speedY = boolpol(steven.pointedUpLast==false) * moveSpeed * 2;
                steven.snapY();
                steven.speedX = -moveSpeed;

                steven.setFacing(Direction::WEST);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
    steven.pointedUpLast=true;
                steven.speedX = boolpol(steven.facingLeft==false) * moveSpeed * 2;
                steven.snapX();

                steven.speedY = -moveSpeed;
                steven.setFacing(Direction::NORTH);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
steven.pointedUpLast=false;
                steven.speedX = boolpol(steven.facingLeft==false) * moveSpeed * 2;
                steven.snapX();

                steven.speedY = moveSpeed;
                steven.setFacing(Direction::SOUTH);
            }

            //now actually move him

            steven.sprite.move(sf::Vector2f(steven.speedX/3 * time.asMilliseconds() /10, steven.speedY/3 * time.asMilliseconds() / 10));

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

        for (int r = 0; r < mapRows; r++)
            for (int c = 0; c < mapCols; c++)
                window.draw(layer1[r][c].sprite);



    	window.draw(steven.sprite);
        gold.draw(window);
        gold2.draw(window);


    	window.draw(HUDsprite);



        //draw the grid
            for (int c = 0; c < 50; c++)
        {
            sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(c*16,0)),
            sf::Vertex(sf::Vector2f(c*16,500))
            };
            //line.color = sf::Color(255,0,0);
            window.draw(line,2,sf::Lines);
        }

//draw the grid
        for (int r = 0; r < 50; r++)
        {
sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0,r*16)),
            sf::Vertex(sf::Vector2f(500*50,r*16))
            };
            //line.color = sf::Color(255,0,0);
            window.draw(line,2,sf::Lines);

        }

        sf::FloatRect visibleArea(steven.x-160/2,steven.y-144/2,160,144);
        HUDsprite.setPosition(steven.x-160/2,steven.y-144/2);
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

if (steven.y-steven.height/2 < 0) steven.setPosition(steven.x,steven.height/2);
if (steven.x-steven.width/2 < 0) steven.setPosition(steven.width/2,steven.y);

}

void doAnimationStuff(int elapsed) {
steven.updateTexture(elapsed);

}
void drawHUD()
{

}
float boolpol(bool yes)
{
    if (yes)
        return 1;
    else
        return -1;
}
