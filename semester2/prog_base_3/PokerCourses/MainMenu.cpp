#include "MainMenu.h"
#include "Consts.h"
MainMenu::MainMenu(RenderWindow* winInput, Game* gameMenuInput)
{
    this->win = winInput;
    this->gameMenu = gameMenuInput;
    backTexture.loadFromFile("img/mainMenuBack.png");
    background.setTexture(backTexture);
    background.setPosition(0, 0);
    background.setScale((float)SCREEN_WIDTH/400, (float)SCREEN_HEIGHT/ 300);

    this->exitBtn = new CallBtn();
    this->multiplayerBtn = new CallBtn();
    this->exitBtn->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    this->multiplayerBtn->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 50);

    exitTexture.loadFromFile("img/singleplayerBTN.png");
    this->exitBtn->sprite.setTexture(exitTexture);

    multiplayerTexture.loadFromFile("img/multiplayerBTN.png");
    this->multiplayerBtn->sprite.setTexture(multiplayerTexture);

}
void MainMenu::start()
{



    // BUTTONS

    while (this->win->isOpen())
    {
        Event event;
        while (this->win->pollEvent(event))
        {
            if (event.type == Event::Closed)
                this->win->close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (this->exitBtn->isPressed(event.mouseButton.x, event.mouseButton.y))
                        return;
                    if (this->multiplayerBtn->isPressed(event.mouseButton.x, event.mouseButton.y))
                    {
                        this->gameMenu->start();
                        return;
                    }
                }
            }


        }

        this->win->draw(background);

        this->win->draw(this->exitBtn->sprite);
        this->win->draw(this->multiplayerBtn->sprite);
        this->win->display();

    }
}
