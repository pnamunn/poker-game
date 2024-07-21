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

    // Dealer::dealCards(inPlayers, deck);
    // Dealer::determineDealer(inPlayers);
    
    // Dealer::setMinBet(5);
    // Dealer::preflopRound(inPlayers);

}

