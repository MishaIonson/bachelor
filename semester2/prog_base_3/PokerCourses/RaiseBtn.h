#include <SFML/Graphics.hpp>

class RaiseBtn{
public:
    bool isPressed(float x, float y);
    RaiseBtn();
    sf::Sprite sprite;
    sf::Texture texture;
private:
    float posX;
    float posY;
    float width;
    float height;
};



