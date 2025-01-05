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
#include <iomanip>
using namespace std;
#include "Card.h"
#include "Deck.h"
#include "Dealer.h"
#include "Player.h"
#include "PlayerList.h"
#include "helpers.h"


// PlayerList inPlayers, outPlayers;
// Deck deck;


int main() {
    srand(time(NULL));      // seed
    PlayerList outPlayers(NULL);
    PlayerList players(&outPlayers);
    Deck deck;
    // Card communityCard[5] = {Card()};
    // vector<Card> communityCards = {};

    int numPlayers;
    cout << "Enter number of players: ";
    cin >> numPlayers;

    for (int i=1; i <= numPlayers; i++) {
        Player *player = new Player();
        players.addPlayer(*player, i);
    }
    
    // players.listPlayers();
    // cout << "done listing players";
    // players.removePlayer("Player2");
    // cout << "just removed player2";
    // players.listPlayers(true);
    // cout << "just listed players after moving one to outList";


    Dealer::dealCards(players, deck);
    Dealer::determineDealer(players);
    clearConsole();
    
    // PREFLOP
    Dealer::setMinBet(5);
    Dealer::preflopRound(players);
    Dealer::goAroundTheTable(players);    // TODO go thru just the remaining players, & continue until an ante is agreed on


    // FLOP
    // communityCard[0] = deck.drawRandomCard();
    // communityCard[1] = deck.drawRandomCard();
    // communityCard[2] = deck.drawRandomCard();
    Dealer::communityCards.push_back(deck.drawRandomCard());
    Dealer::communityCards.push_back(deck.drawRandomCard());
    Dealer::communityCards.push_back(deck.drawRandomCard());

    clearConsole();
    cout << setw(15) << "** You made it to the Flop! **\n"
         << "The first 3 community cards are:\n   " 
         << Dealer::communityCards[0].toString() << "\n   "
         << Dealer::communityCards[1].toString() << "\n   "
         << Dealer::communityCards[2].toString();
    enterToContinue();
    
    Dealer::goAroundTheTable(players);

    // TURN
    cout << "\n Welcome to the turn!";
    enterToContinue();

    Dealer::goAroundTheTable(players);


    // RIVER


    // SHOWDOWN
}

// TODO NEXT: test files needed for Card and Deck
