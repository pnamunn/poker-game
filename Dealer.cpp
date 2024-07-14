#include "Dealer.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "PlayerList.h"
#include "math.h"


Dealer::Dealer() {}


/*static*/ void Dealer::determineDealer(PlayerList &inPlayers) {
    int chosenPlayer = rand() % (inPlayers.length) + 1;
    cout << chosenPlayer;
    inPlayers = inPlayers.changeHead(chosenPlayer);
    cout << "\t\t\t\t\t *" << inPlayers.head->name << " will act as this game's dealer*\n\n";
}


/*static*/ void Dealer::dealCards(PlayerList &inPlayers, Deck &deck) {
    Player *curr = inPlayers.head;
    while(curr != NULL) {
        cout << "Dealing cards to " << curr->name << "...\n";
        curr->cards[0] = deck.drawRandomCard();
        curr->cards[1] = deck.drawRandomCard();
        // TODO remove cards from deck
                
        // cout << curr->cards[0].getSuitName() << ", " << curr->cards[0].getValueName() << "\t" 
        //     << curr->cards[1].getSuitName() << ", " << curr->cards[1].getValueName() << "\n"; 
        curr = curr->next;

        // deck.printDeck();

    // iterates thru deck & prints each card out
    // curr = inPlayers.head;
    // while(curr != NULL) {
    //     cout << curr->c
    }
    
}

/*static*/ void Dealer::flipCard() {
    // Card cardDrawn = Deck.drawRandomCard;
    // Deck.removeCardFromDeck(cardDrawn);
    // cout << 
}

/*static*/ void Dealer::flop() {
    
}

/*static*/ void Dealer::preflopRound(PlayerList &players) {
    cin.ignore();   // clear buffer before using cin.get()

    // Small blind //
    Player *curr = players.head->next;
    int smallBlind = floor(Dealer::getMinBet() / 2);
    string temp;
    cout << "\t\t\t\t\t ***** IT'S " << curr->name << "'s TURN *****\n\n";
    cout << "\t\t\t\t\t press enter to post the small blind of " << smallBlind << " chips ->\n";
    cin.get();
    curr->placeBet(smallBlind);
    cout << "\t\t\t\t\t " << "After the small blind, you have " << curr->chips << " chips\n\n";
    cout << "\t\t\t\t\t press enter to end your turn -> ";
    cin.get();

    // Big blind //
    curr = curr->next;
    int bigBlind;
    curr->turnHeader();
    Player::clearConsole();
    cout << "\t\t\t\t\t***** FOR " << curr->name << "'S EYES ONLY *****\n\n";
    cout << "\t Chips: " << curr->chips << "\n";
    cout << "\t\t\t\t " << "Choose a big blind value to bet (>= " << Dealer::getMinBet() << "): ";
    cin >> bigBlind;    // TODO error checking
    cout << "\t\t\t\t\t You posted a big blind of " << bigBlind << " and have " << curr->chips << " left\n\n";
    curr->placeBet(bigBlind);
    cout << "\t\t\t\t\t press enter to end your turn -> ";
    cin.ignore();
    cin.get();
    curr = curr->next;

    // Remaining bets //
    while(curr != NULL) {
        curr->turnHeader();
        curr->prompt();
        curr = curr->next;

    }

    cout << "preFlop round done";
}

// Initialize static data members
int Dealer::pool = 0;
int Dealer:: minBet = 5;

//  S   E   T   T   E   R   S   &
//  G   E   T   T   E   R   S

/*static*/ void Dealer::addToPool(int num) {
    Dealer::pool += num;
}

/*static*/ void Dealer::setMinBet(int num) {
    Dealer::minBet = num;
}

/*static*/ const int Dealer::getMinBet() {
    return Dealer::minBet;
}



