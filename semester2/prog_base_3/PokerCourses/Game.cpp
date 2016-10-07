#include "Game.h"
#include <sstream>
#include <iostream>


Game::Game(RenderWindow* winInput)
{
    this->win = winInput;
    round = 0;
    this->aiObject = new AI();
    moveDone = -1;
    doNotRedraw = false;
}

void Game::nextDistribution()
{
    bank = 0;
    for (int i = 0; i < 5; i++)
        bet[i] = 0;
    round = 0;
    for (int i = 0; i < 5; i++)
        if (player[i]->inGame == 1)
            player[i]->inDistribution = 1;



    deck->putRandom();
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            *(player[i]->card[j]) = deck->getCard();
            player[i]->card[j]->visible = false;
            if (i == 0)
                player[i]->card[j]->visible = true;
        }


        *tableCard[i] = deck->getCard();
        tableCard[i]->sprite.setPosition(i * 100 + 190, 0);
        tableCard[i]->setTexture();
        tableCard[i]->visible = false;

    }

    for (int i =0; i < 2; i++)
    {
        player[0]->card[i]->sprite.setPosition(i*100 + 300, 400);
        player[0]->card[i]->setTexture();

        player[1]->card[i]->sprite.setPosition(i*100, 200);
        player[1]->card[i]->setTexture();

        player[2]->card[i]->sprite.setPosition(i*100, 300);
        player[2]->card[i]->setTexture();

        player[3]->card[i]->sprite.setPosition(SCREEN_WIDTH - i*100 - 100, 200);
        player[3]->card[i]->setTexture();

        player[4]->card[i]->sprite.setPosition(SCREEN_WIDTH - i*100- 100, 300);
        player[4]->card[i]->setTexture();
    }

    for (int i = 1; i < 5; i++)
        for (int j = 0; j < 2; j++)
            player[i]->card[j]->visible = false;
}

void Game::makeTableCardTexturesFresh()
{
    for (int i = 0; i < 5; i++)
    {
        tableCard[i]->setTexture();
    }
}

void Game::makeFreshUsersCards()
{
    int USERS = 0;
    for (int i = 0; i < 5; i++)
        if (player[i]->inDistribution == 1)
            USERS++;
    for (int i = 0; i < 5; i++)
    {
        tableCard[i]->setTexture();
        if (i < USERS)
        {
            player[i]->card[0]->setTexture();
            player[i]->card[1]->setTexture();
        }
    }

    int user1_card1_value = player[0]->card[0]->getValueIdentifier();
    int user1_card1_color = player[0]->card[0]->getColorIdentifier();

    int user1_card2_value = player[0]->card[1]->getValueIdentifier();
    int user1_card2_color = player[0]->card[1]->getColorIdentifier();

    int user2_card1_value = player[currentID]->card[0]->getValueIdentifier();
    int user2_card1_color = player[currentID]->card[0]->getColorIdentifier();

    int user2_card2_value = player[currentID]->card[1]->getValueIdentifier();
    int user2_card2_color = player[currentID]->card[1]->getColorIdentifier();

    player[0]->card[0]->setValueIdentifier(user2_card1_value);
    player[0]->card[0]->setColorIdentifier(user2_card1_color);
    player[0]->card[1]->setValueIdentifier(user2_card2_value);
    player[0]->card[1]->setColorIdentifier(user2_card2_color);

    player[currentID]->card[0]->setValueIdentifier(user1_card1_value);
    player[currentID]->card[0]->setColorIdentifier(user1_card1_color);
    player[currentID]->card[1]->setValueIdentifier(user1_card2_value);
    player[currentID]->card[1]->setColorIdentifier(user1_card2_color);

    player[0]->card[0]->setTexture();
    player[0]->card[1]->setTexture();
    player[0]->card[0]->setTexture();
    player[0]->card[1]->setTexture();

    player[currentID]->card[0]->setTexture();
    player[currentID]->card[1]->setTexture();
    player[currentID]->card[0]->setTexture();
    player[currentID]->card[1]->setTexture();


    player[0]->card[0]->setValueIdentifier(user1_card1_value);
    player[0]->card[0]->setColorIdentifier(user1_card1_color);
    player[0]->card[1]->setValueIdentifier(user1_card2_value);
    player[0]->card[1]->setColorIdentifier(user1_card2_color);

    player[currentID]->card[0]->setValueIdentifier(user2_card1_value);
    player[currentID]->card[0]->setColorIdentifier(user2_card1_color);
    player[currentID]->card[1]->setValueIdentifier(user2_card2_value);
    player[currentID]->card[1]->setColorIdentifier(user2_card2_color);
}

const int CLIENTS_NUM = 1;

void Game::server()
{
    currentID = 0;
    for (int i = 0; i < 5; i++)
    {
        player[i]->inGame = 0;
        player[i]->inDistribution = 0;
        player[i]->purse = 20;
    }
    player[0]->inGame = 1;
    player[0]->inDistribution = 1;


    listener.listen(53000);

    thisDevicePlayerTurn = false;
    for (int i = 0; i < CLIENTS_NUM; i++)
    {
        listener.accept(clients[i]);
        player[i + 1]->inGame = 1;
        player[i + 1]->inDistribution = 1;
    }
    thisDevicePlayerTurn = true;


    sendAllDataToClients();


    int k;
    while(true)
    {
        thisDevicePlayerTurn = true;
        moveDone = -1;
        while(moveDone == -1){std::cout << "";}

        if (moveDone == 0)
        {
            int maximal = bet[0];
            for (int i = 0; i < 5; i++)
                if (maximal < bet[i])
                    maximal = bet[i];
            bet[0] = maximal;
        }
        else if (moveDone == 1)
        {
            if (player[0]->purse >= 1)
            {
                int maximal = bet[0];
                for (int i = 0; i < 5; i++)
                    if (maximal < bet[i])
                        maximal = bet[i];
                maximal++;
                bet[0] = maximal;
            }
        }
        else if (moveDone == 2)
            player[0]->inDistribution = 0;

        thisDevicePlayerTurn = false;
        std::cout <<"_________misha________\n";

        for (int i = 0; i < CLIENTS_NUM; i++)
        {
            sendAllDataToClients();

            if (player[i + 1]->inDistribution == 0)
                continue;

            packetReceive.clear();
            packetSend.clear();
            packetSend << -1; // means server waits for an answer
            clients[i].send(packetSend);
            clients[i].receive(packetReceive);

            packetReceive >> k;
            std::cout <<"got: " << k << " -----------\n";
            /*
            *   0 - call
            *   1 - raise
            *   2 - fold
            */

            if (k == 0)
            {
                int maximal = bet[0];
                for (int i = 0; i < 5; i++)
                    if (maximal < bet[i])
                        maximal = bet[i];
                bet[i + 1] = maximal;
            }
            else if (k == 1)
            {
                if (player[i + 1]->purse - bet[i + 1] >= 1)
                {
                    int maximal = bet[0];
                    for (int j = 0; j < 5; j++)
                        if (maximal < bet[j])
                            maximal = bet[j];
                    maximal++;
                    bet[i + 1] = maximal;
                }
            }
            else if (k == 2)
                player[i + 1]->inDistribution = 0;


        }
        sendAllDataToClients(); // @DELETE


        bool repeat = false;
        for (int i = 0; i < CLIENTS_NUM; i++)
            if (bet[i] != bet[i + 1])
                repeat = true;


        int playersOnDistribution = 0;
        int theOnlyPlayerIndex = 0;
        for (int i = 0; i < CLIENTS_NUM + 1; i++)
        {
            if (player[i]->inDistribution == 1)
            {
                theOnlyPlayerIndex = i;
                playersOnDistribution++;
            }
        }

        if ((repeat) && (playersOnDistribution > 1))
            continue; // do the round again





        if (playersOnDistribution > 1)
            nextRound();

        if ((round == 5) || (playersOnDistribution <= 1))
        {
            if (playersOnDistribution <= 1)
            {
                for (int i = 0; i < CLIENTS_NUM + 1; i++)
                    bank += bet[i];
                player[theOnlyPlayerIndex]->purse += bank;
            }
            nextDistribution();
        }
        sendAllDataToClients();
    }
}

void Game::sendAllDataToClients()
{
    for (int c = 1; c <= CLIENTS_NUM; c++)
    {
        packetSend.clear();
        packetSend << c; // id

        packetSend << round;
        for (int i = 0; i < 5; i++)
        {
            packetSend << bet[i];
        }

        for (int i = 0; i < 5; i++)
            packetSend << player[i]->inDistribution;

        for (int i = 0; i < 5; i++)
            packetSend << player[i]->inGame;


        int k;

        std::cout << "SENDING\n";
        for (int i = 0; i < 5; i++)
        {
            k = tableCard[i]->getValueIdentifier();
            packetSend << k;
            std::cout <<"table card " << i << " value: " <<  k << std::endl;
            k = tableCard[i]->getColorIdentifier();
            packetSend << k;
            std::cout <<"table card " << i << " color: " <<  k << std::endl;
        }

        for (int i = 0; i < 5; i++)
        {
            k = player[i]->card[0]->getValueIdentifier();
            packetSend << k;

            k = player[i]->card[0]->getColorIdentifier();
            packetSend << k;

            k = player[i]->card[1]->getValueIdentifier();
            packetSend << k;

            k = player[i]->card[1]->getColorIdentifier();
            packetSend << k;
        }

        for (int i = 0; i < 5; i++)
        {
            k = player[i]->purse;
            packetSend << k;
        }
        k = bank;
        packetSend << k;
        clients[c - 1].send(packetSend);
    }

}


void Game::client()
{
    sleep(sf::seconds(1));
    clientSocket.connect("192.168.1.100", 53000);

    int k;
    clientSocket.receive(packetReceive);
    packetReceive >> k;
    std::cout << "id: " <<  k << std::endl;
    currentID = k;
    getAllDataFromServer();
    doNotRedraw = true;
    makeFreshUsersCards();
    doNotRedraw = false;

    thisDevicePlayerTurn = false;
    while(true)
    {
        if (!thisDevicePlayerTurn)
        {
            packetReceive.clear();
            clientSocket.receive(packetReceive);
            packetReceive >> k;
            if (k == -1)
            {
                std::cout << "TAKEN INFO, THAT NOW IS MY TURN" << std::endl;
                moveDone = -1;
                thisDevicePlayerTurn = true;
            }
            else
            {
                currentID = k;
                std::cout << "id: " <<  k << std::endl;
                getAllDataFromServer();
            }
        }
        else if (moveDone != -1)
        {
            std::cout << "DATA SENT TO SERVER ---------------\n";
            packetSend.clear();
            packetSend << moveDone;
            clientSocket.send(packetSend);
            thisDevicePlayerTurn = false;
        }
    }
}

void Game::getAllDataFromServer()
{

    int k;

    bool afterDistribution = false;



    packetReceive >> k;
    if ((round != k) && (k > round))
        nextRound();
    else if ((round != k) && (k < round))
    {
        nextDistribution();
        afterDistribution = true;
    }

    std::cout << "round: " <<  k << std::endl;
    for (int i = 0; i < 5; i++)
    {
        packetReceive >> k;
        bet[i] = k;
        std::cout << "bet: " <<  k << std::endl;
    }

    for (int i = 0; i < 5; i++)
    {
        packetReceive >> k;
        player[i]->inDistribution = k;
        std::cout << "isDistribution: " <<  k << std::endl;
    }

    for (int i = 0; i < 5; i++)
    {
        packetReceive >> k;
        player[i]->inGame = k;
        std::cout << "inGame: " <<  k << std::endl;
    }
    std::cout << std::endl;


    for (int i = 0; i < 5; i++)
    {
        packetReceive >> k;
        tableCard[i]->setValueIdentifier(k);
        std::cout <<"table card " << i << " value: " <<  k << std::endl;
        packetReceive >> k;
        tableCard[i]->setColorIdentifier(k);
        std::cout <<"table card " << i << " color: " <<  k << std::endl;
    }
     std::cout << std::endl;

    for (int i = 0; i < 5; i++)
    {
        packetReceive >> k;
        player[i]->card[0]->setValueIdentifier(k);

        packetReceive >> k;
        player[i]->card[0]->setColorIdentifier(k);

        packetReceive >> k;
        player[i]->card[1]->setValueIdentifier(k);

        packetReceive >> k;
        player[i]->card[1]->setColorIdentifier(k);
    }

    for (int i = 0; i < 5; i++)
    {
        packetReceive >> k;
        player[i]->purse = k;
    }

    packetReceive >> k;
    bank = k;

    makeTableCardTexturesFresh();

    if (afterDistribution)
    {
        doNotRedraw = true;
        makeFreshUsersCards();
        doNotRedraw = false;
        afterDistribution = false;
    }
}


void Game::refreshText()
{
    std::stringstream ss;
    ss.clear();
    ss << bank;
    bankText.setString("Bank: " + ss.str());

    for (int i = 0; i < 5; i++)
    {
        std::stringstream stream;
        stream << bet[i];
        stream << " / ";
        stream << player[i]->purse;
        betText[i].setString(stream.str());
    }

    if (currentID != 0) // to show the user's data
    {
        std::stringstream streamster;
        streamster << bet[currentID];
        streamster << " / ";
        streamster << player[currentID]->purse;
        betText[0].setString(streamster.str());


        std::stringstream streamw;
        streamw.clear();
        streamw << bet[0];
        streamw << " / ";
        streamw << player[0]->purse;
        betText[currentID].setString(streamw.str());
    }
}


void Game::start()
{
    this->deck = new Deck();
    deck->putRandom();
    Texture cardTexture;

    Sprite background;
    Texture backTexture;
    backTexture.loadFromFile("img/background.png");
    background.setTexture(backTexture);
    background.setPosition(0, 0);
    background.setScale((float)SCREEN_WIDTH/400, (float)SCREEN_HEIGHT/ 300);

    // BUTTONS
    this->callButton = new CallBtn();
    this->foldButton = new FoldBtn();
    this->raiseButton = new RaiseBtn();


    for (int i = 0; i < 5; i++)
    {
        player[i] = new Hand();
        this->tableCard[i] = new Card();
        this->player[i]->ID = i;
    }

    this->nextDistribution();

    waitText.setCharacterSize(26);
    waitText.setPosition(0, SCREEN_HEIGHT - 80);
    waitText.setString("wait");
    bankText.setCharacterSize(24);
    bankText.setPosition(SCREEN_WIDTH/2 - 20, SCREEN_HEIGHT/2);
    betText[0].setPosition(SCREEN_WIDTH/2 - 20, SCREEN_HEIGHT - 170);
    betText[1].setPosition(100, 150);
    betText[2].setPosition(100, 290);
    betText[3].setPosition(SCREEN_WIDTH - 100, 150);
    betText[4].setPosition(SCREEN_WIDTH - 100, 290);


    sf::Font font;
    font.loadFromFile("fonts/groovy.ttf");
    bankText.setFont(font);
    waitText.setFont(font);
    for (int i = 0; i < 5; i++)
    {
        betText[i].setCharacterSize(18);
        betText[i].setFont(font);
    }


    // NETWORK
    // @TODO: REPLACE
    static sf::Thread serverThread(&Game::server, this);
    serverThread.launch();


    //
    //static sf::Thread clientThread(&Game::client, this);
    //clientThread.launch();
    //
    //


    while (this->win->isOpen())
    {
        if (doNotRedraw)
            continue;
        Event event;
        while (this->win->pollEvent(event))
        {
            if (event.type == Event::Closed)
                this->win->close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if ((thisDevicePlayerTurn) && (event.mouseButton.button == sf::Mouse::Left))
                {
                    if (callButton->isPressed(event.mouseButton.x, event.mouseButton.y))
                        moveDone = 0;
                    if (raiseButton->isPressed(event.mouseButton.x, event.mouseButton.y))
                        moveDone = 1;
                    if (foldButton->isPressed(event.mouseButton.x, event.mouseButton.y))
                        moveDone = 2;
                }
            }


        }

        this->refreshText();
        this->win->clear();
        this->win->draw(background);

        this->win->draw(bankText);
        for (int i = 0; i < 5; i++)
            if (player[i]->inGame == 1)
                win->draw(betText[i]);

        for (int i = 0; i < 5; i++)
        {
            if (tableCard[i]->visible)
                this->win->draw(tableCard[i]->sprite);
            for (int j = 0; j < 2; j++)
                if ((player[i]->card[j]->visible) && (player[i]->inDistribution == 1) && (player[i]->inGame == 1))
                    this->win->draw(player[i]->card[j]->sprite);
        }
        this->win->draw(callButton->sprite);
        this->win->draw(foldButton->sprite);
        this->win->draw(raiseButton->sprite);
        if (!thisDevicePlayerTurn)
            this->win->draw(waitText);


        this->win->display();

    }

}

void Game::nextRound()
{
    if (currentID == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            bank+=bet[i];
            player[i]->purse -= bet[i];
            bet[i] = 0;
        }
    }


    if (round < 3)
        round++;
    else
    {
        int winner = whoWon();
        std::cout << winner << " wins" << std::endl;
        for (int i = 1; i < 5; i++)
            for (int j = 0 ; j < 2; j++)
                player[i]->card[j]->visible = true;
        if ((currentID == 0) && (round == 3))
            player[winner]->purse += bank;
        round++;
        if (round == 5)
            for (int i = 1; i < 5; i++)
                for (int j = 0 ; j < 2; j++)
                    player[i]->card[j]->visible = false;

        return;
    }


    if (round == 1)
    {
        for (int i = 0; i < 3; i++)
            this->tableCard[i]->visible = true;
    }
    else if (round == 2)
        this->tableCard[3]->visible = true;
    else if (round == 3)
        this->tableCard[4]->visible = true;
}

int Game::whoWon()
{
    int USERS = 0;
    for (int i = 0; i < 5; i++)
        if (player[i]->inDistribution == 1)
        USERS++;

    int straight[13];
    int powerP[USERS][2]; // 0 - power, 1 - card

    /*
    *   POWER LIST:
    *   0 - HIGH HAND
    *   1 - PAIR
    *   2 - TWO PAIRS
    *   3 - SET
    *   4 - STRAIGHT
    *   5 - FLUSH
    *   6 - FULL HOUSE
    *   7 - FOUR OF A KIND
    */

    for (int pI = 0; pI < USERS; pI++)
    {
        for (int i = 0; i < 13; i++)
                straight[i] = 0;


        for (int i = 0; i < 5; i++)
            straight[this->tableCard[i]->getValueIdentifier()]++;

        straight[this->player[pI]->card[0]->getValueIdentifier()]++;
        straight[this->player[pI]->card[1]->getValueIdentifier()]++;

        powerP[pI][0] = 0;
        powerP[pI][1] = this->aiObject->findHighHand(this->player[pI]->card);
        if (this->aiObject->findPair(straight) != -1)
        {
            powerP[pI][0] = 1;
            powerP[pI][1] = this->aiObject->findPair(straight);
        }
        if (this->aiObject->findTwoPairs(straight) != -1)
        {
            powerP[pI][0] = 2;
            powerP[pI][1] = this->aiObject->findTwoPairs(straight);
        }
        if (this->aiObject->findSet(straight) != -1)
        {
            powerP[pI][0] = 3;
            powerP[pI][1] = this->aiObject->findSet(straight);
        }
        if (this->aiObject->findStraight(straight) != -1)
        {
            powerP[pI][0] = 4;
            powerP[pI][1] = this->aiObject->findStraight(straight);
        }
        if (this->aiObject->findFlush(tableCard, this->player[pI]->card[0], this->player[pI]->card[1]) != -1)
        {
            // @TODO: find solution for unworking flushfinder
            powerP[pI][0] = 5;
            powerP[pI][1] = this->aiObject->findFlush(tableCard, this->player[pI]->card[0], this->player[pI]->card[1]);
        }
        if (this->aiObject->findFullHouse(straight) != -1)
        {
            powerP[pI][0] = 6;
            powerP[pI][1] = this->aiObject->findFullHouse(straight);
        }
        if (this->aiObject->findFourOfAKind(straight) != -1)
        {
            powerP[pI][0] = 7;
            powerP[pI][1] = this->aiObject->findFourOfAKind(straight);
        }
    }

    int answer = 0;
    for (int i = 1; i < USERS; i++)
    {
        if (powerP[i][0] > powerP[answer][0])
            answer = i;
         else if ((powerP[i][0] == powerP[answer][0]) && (powerP[i][1] > powerP[answer][1]))
            answer = i;
        else if ((powerP[i][0] == powerP[answer][0]) && (powerP[i][1] == powerP[answer][1]))
        {
            if (this->aiObject->findHighHand(this->player[i]->card) > this->aiObject->findHighHand(this->player[answer]->card))
                answer = i;
        }
    }

    return answer;
}


