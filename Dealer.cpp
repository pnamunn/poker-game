#include "Dealer.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "PlayerList.h"
#include "math.h"
#include "math.h"


Dealer::Dealer() {}

// Initialize static data members
int Dealer::pool = 0;
int Dealer:: minBet, Dealer::roundMin = 5;

/*static*/ void Dealer::determineDealer(PlayerList &inPlayers) {
    int chosenPlayer = rand() % (inPlayers.length) + 1;
    cout << chosenPlayer;
    inPlayers = inPlayers.changeHead(chosenPlayer);
    cout << "\t\t\t\t\t *" << inPlayers.head->name << " will act as this game's dealer*\n\n";
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

/*static*/ void Dealer::preflopRound(PlayerList &inPlayers, PlayerList &outPlayers) {

    // Small blind //
    Player *curr = inPlayers.head->next;
    int smallBlind = floor(Dealer::getMinBet() / 2);
    string temp;
    cout << "\t\t\t\t\t ***** IT'S " << curr->name << "'s TURN *****\n\n";
    cout << "\t\t\t\t\t press enter to post the small blind of " << smallBlind << " chips -> ";
    cin.ignore();   // clear buffer after cin >> was used (in getting the number of players in main)
    cin.ignore(1000, '\n');
    // cin.get();
    curr->placeBet(smallBlind);
    cout << "\t\t\t\t " << "After the small blind, you have " << curr->chips << " chips left\n\n";
    cout << "\t\t\t\t\t press enter to end your turn -> ";
    cin.ignore(1000, '\n');
    // do { getline(cin, temp);} while(temp.length() != 0);

    // Big blind //
    curr = curr->next;
    int bigBlind;
    Player::clearConsole();
    cout << "\t\t\t\t\t ***** IT'S " << curr->name << "'s TURN *****\n\n";
    cout << "\t Chips: " << curr->chips << "\n";
    cout << "\t\t\t\t\t " << "Choose a big blind value to bet (>= " << Dealer::getMinBet() << "): ";
    cin >> bigBlind;    // TODO error checking
    Dealer::setRoundMin(bigBlind);
    curr->placeBet(bigBlind);
    cout << "\t\t\t\t You posted a big blind of " << bigBlind << " and have " << curr->chips << " chips left.\n\n";
    cout << "\t\t\t\t\t press enter to end your turn -> ";
    cin.ignore();   // clear buffer after cin << was used
    cin.ignore(1000, '\n');

    // Remaining bets //
    curr = curr->next;
    while(curr != NULL) {
        curr->turnHeader();
        curr->prompt();
        curr = curr->next;
    }

    cout << "preFlop round done";
}


//  S   E   T   T   E   R   S   &
//  G   E   T   T   E   R   S

/*static*/ void Dealer::addToPool(int num) {
    Dealer::pool += num;
/*static*/ void Dealer::addToPool(int num) {
    Dealer::pool += num;
}

/*static*/ void Dealer::setMinBet(int num) {
    Dealer::minBet = num;
    Dealer::minBet = num;
}
/*static*/ const int Dealer::getMinBet() {
    return Dealer::minBet;
}

/*static*/ void Dealer::setRoundMin(int num) {
    Dealer::roundMin = num;
}
/*static*/ const int Dealer::getRoundMin() {
    return Dealer::roundMin;
}



