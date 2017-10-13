#include "SFML/Graphics.hpp"
#include <string>
using namespace std;

class ground
{
public:
    ground();
    ~ground();

    void loadTexture(string imagePath);
    void setPosition(float x, float y);

    sf::Sprite sprite;
    sf::Texture texture;
    float width, height;
    float x, y;
};
