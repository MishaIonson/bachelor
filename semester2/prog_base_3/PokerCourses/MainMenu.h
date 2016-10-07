#include "Consts.h"
#include "Game.h"
#include "SFML/Audio.hpp"

class MainMenu{
private:
    RenderWindow* win;
    CallBtn* multiplayerBtn;
    CallBtn* exitBtn;
    Texture exitTexture;
    Texture multiplayerTexture;

    Sprite background;
    Texture backTexture;
    Game *gameMenu;
public:
    MainMenu(RenderWindow* winInput, Game* gameMenuInput);
    void start();
};
