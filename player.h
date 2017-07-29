#include "SFML/Graphics.hpp"
#include <string>
using namespace std;
class player {
 public:
player();
~player();

void pls();
void loadTexture(string imagePath);
void setPosition(float x, float y);

sf::Sprite sprite;
sf::Texture texture;
float x, y, lx, ly;

const static float base_speed = 0.25;

};
