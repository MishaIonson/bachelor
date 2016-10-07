#include <SFML/Graphics.hpp>

class CallBtn{
public:
    bool isPressed(float x, float y);
    CallBtn();
    sf::Sprite sprite;
    sf::Texture texture;
    void called(int playerID, int* bet, int* playersPurse);
    void setPosition(float x, float y);
private:
    float posX;
    float posY;
    float width;
    float height;
};
