#include "SFML/Graphics.hpp"
#include <string>
using namespace std;
class player {
 public:
player();
~player();

void pls();
void loadTexture(string imagePath);
void updateTexture(int elapsed);
void setPosition(float x, float y);
void setFacing(bool left);

sf::Sprite sprite;
sf::Texture texture;
float x, y, lx, ly;
float width,height;
int spriteCycleSpeed;
int spriteCycleCounter;
int currentSprite;
bool facingLeft;

const static float base_speed = 0.25;

};
