#include <SFML/Graphics.hpp>

class FoldBtn{
public:
    bool isPressed(float x, float y);
    FoldBtn();
    sf::Sprite sprite;
    sf::Texture texture;
private:
    float posX;
    float posY;
    float width;
    float height;
};


