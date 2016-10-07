#include "Deck.h"
#include "CallBtn.h"
#include "FoldBtn.h"
#include "RaiseBtn.h"
#include "Consts.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "AI.h"
#include "Hand.h"
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class Game
{
public:
    Game(RenderWindow* winInput);
    void start();
    bool isClient;
private:
    bool thisDevicePlayerTurn;
    bool doNotRedraw;
    AI *aiObject;
    sf::Text bankText;
    sf::Text betText[5];
    sf::Text waitText;
    void makeTableCardTexturesFresh();
    int round;
    int moveDone;
    RenderWindow* win;
    void nextRound();
    void nextDistribution();
    Card* tableCard[5];
    Hand* player[5];
    Deck* deck;
    CallBtn* callButton;
    FoldBtn* foldButton;
    RaiseBtn* raiseButton;
    int cash;
    int bank;
    int bet[5];
    int currentID;
    void refreshText();
    void aiMoves();
    int whoWon();
    void server();
    void client();
    void sendDataToServer();
    sf::Packet packetSend;
    sf::Packet packetReceive;
    sf::TcpListener listener;
    sf::TcpSocket clients[5];
    void sendAllDataToClients();
    void getAllDataFromServer();
    sf::TcpSocket clientSocket;
    void makeFreshUsersCards();

};
