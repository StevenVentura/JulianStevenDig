#include "SFML/Graphics.hpp"
#include <string>
#include "player.h"
using namespace std;

class chest
{
public:
    chest();
    ~chest();

    void loadTexture(string imagePath);
    void setPosition(float x, float y);
    void hitboxes();
    void draw(sf::RenderWindow&);
    void doIntersectionCheck(player&,sf::Time&);

    sf::Sprite sprite;
    sf::Texture texture;
    sf::RectangleShape rectangle;
    sf::RectangleShape rectangle2;
    sf::RectangleShape rectangle3;
    sf::RectangleShape rectangle4;

    float x, y, width, height;
    int distance;
};
