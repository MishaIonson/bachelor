#include "MainMenu.h"

int main()
{
    sf::Music music;
    music.openFromFile("sound/music.ogg");
    music.play();
    music.setLoop(true);
    RenderWindow win(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Poker Courses");

    Game* gameMenu = new Game(&win);

    MainMenu *mainMenu = new MainMenu(&win, gameMenu);
    mainMenu->start();

    return 0;
}
