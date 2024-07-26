// No-limit Texas Hold'em

#ifdef _WIN32
    #include <windows.h>

#elif __unix__              //  TODO test on unix system
    #include <unistd.h>

#endif

#include <iostream>
#include <vector>
#include <string>
#include <string>
#include <cstdlib>
using namespace std;
#include "Card.h"
#include "Deck.h"
#include "Dealer.h"
#include "Player.h"
#include "PlayerList.h"


// PlayerList inPlayers, outPlayers;
// Deck deck;


int main() {
    srand(time(NULL));      // seed
    // PlayerList inPlayers, outPlayers;
    PlayerList inPlayers = new PlayerList(true);
    Deck deck;

    int numPlayers;
    cout << "Enter number of players: ";
    cin >> numPlayers;

    for (int i=1; i <= numPlayers; i++) {
        Player *player = new Player();
        inPlayers.addPlayer(*player, i);
    }
    inPlayers.listPlayers();

    // cout << inPlayers.outList;
    // cout << inPlayers.outList->head << "\n";

    // inPlayers.outList->outList = NULL;
    // cout << inPlayers.outList->outList;
    // cout << inPlayers.outList << "\n";
    // cout << inPlayers.outList->head;

    // inPlayers.removePlayer("Player3");
    // inPlayers.listPlayers();

    // inPlayers.changeHead(4);
    // inPlayers.listPlayers();




    Dealer::dealCards(inPlayers, deck);
    Dealer::determineDealer(inPlayers);
    
    // Dealer::setMinBet(5);
    // Dealer::preflopRound(inPlayers);

}

