// No-limit Texas Hold'em

#ifdef _WIN32
    #include <windows.h>

#elif __unix__              //  TODO test on unix system
    #include <unistd.h>

#endif

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
#include "Card.h"
#include "Deck.h"
#include "Dealer.h"
#include "Player.h"
#include "PlayerList.h"


void clearConsole() {
    #if _WIN32
        system("cls");
    #elif __unix__ 
        system("clear");
    #endif
}

//Globals
int minBet = 5;


PlayerList inPlayers, outPlayers;
Deck deck;


int main() {
    srand(time(NULL));      // seed

    int numPlayers;
    cout << "Enter number of players: ";
    cin >> numPlayers;

    for (int i=1; i <= numPlayers; i++) {
        Player *player = new Player();
        inPlayers.addPlayer(*player, i);
    }

    Dealer::dealCards(inPlayers, deck);
    Dealer::determineDealer(inPlayers);
    
    cout << "\n\nMain In player list:\n";
    inPlayers.listPlayers();



}