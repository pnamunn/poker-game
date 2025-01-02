#include "Dealer.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "PlayerList.h"
#include "helpers.h"
#include "math.h"


Dealer::Dealer() {}

// Initialize static data members
int Dealer::pool = 0;
int Dealer::minBet, Dealer::roundMin = 5;
vector<Card> Dealer::communityCards;

/*static*/ void Dealer::determineDealer(PlayerList &inPlayers) {
    int chosenPlayer = rand() % (inPlayers.getLength()) + 1;     // range [1, inPlayer's length]
    // // cout << chosenPlayer;
    inPlayers.changeHead(chosenPlayer);
    cout << "* " << inPlayers.head->name << " will act as this game's dealer *";
    enterToContinue();
}


/*static*/ void Dealer::dealCards(PlayerList &inPlayers, Deck &deck) {
    Player *curr = inPlayers.head;
    do {
        // cout << "Dealing cards to " << curr->name << "...\n";
        curr->cards[0] = deck.drawRandomCard();
        curr->cards[1] = deck.drawRandomCard();
        curr = curr->next;
    } while(curr != inPlayers.head);
    
}

// /*static*/ void Dealer::flipCard() {
//     Card communityCard = Deck::drawRandomCard();
//     Deck.removeCardFromDeck(cardDrawn);
//     // cout << 
// }

/*static*/ void Dealer::preflopRound(PlayerList &inPlayers) {
    // Small blind
    Player *curr = inPlayers.head->next;
    int smallBlind = floor(Dealer::getMinBet() / 2);
    string temp;
    curr->placeBet(smallBlind);
    cout << "\n" << setw(15) << "***** " << curr->name << "'s turn *****"
    // cout << "\t\t\t\t\t press enter to post the small blind of " << smallBlind << " chips -> ";
    // cin.ignore();   // clear buffer after cin >> was used (in getting the number of players in main)
    // cin.ignore(1000, '\n');
         << "\n"
         << "\n" << "You gave the small blind of " << smallBlind
         << "\n" << "You now have " << curr->chips << " chips left.";
    enterToContinue();
    // cout << "\t\t\t\t\t press enter to end your turn -> ";
    // cin.ignore(1000, '\n');
    // do { getline(cin, temp);} while(temp.length() != 0);
    clearConsole();

    // Big blind
    curr = curr->next;
    int bigBlind;
    cout << "\n" << setw(15) << "***** " << curr->name << "'s turn *****"
         << "\n"
         << "\n" << "Chips: " << curr->chips
         << "\n" << "Choose a big blind value to bet (>= " << Dealer::getMinBet() << "): ";
    cin >> bigBlind;
    bigBlind = errorCheck(bigBlind, GTE, Dealer::getMinBet(),
                          ("\t Try again, your big blind has to be >= " + to_string(Dealer::getMinBet()) + ": "));
    Dealer::setRoundMin(bigBlind);
    curr->placeBet(bigBlind);
    cout << "You now have " << curr->chips << " chips left.";
    enterToContinue();
    // cout << "\t\t\t\t\t press enter to end your turn -> ";
    // cin.ignore();   // clear buffer after cin << was used for bigBlind
    // cin.ignore(1000, '\n');
}

/*static*/ void Dealer::goAroundTheTable(PlayerList &inPlayers) {
    // TODO change to be compatible with doubly linked circular list
    Player *curr = inPlayers.head->next;
    while(curr != NULL) {
        // curr->turnHeader();
        clearConsole();
        cout << setw(15) << "***** For " << curr->name << "'s eyes only *****\n";
        enterToContinue();

        clearConsole();
        curr->outputChipsAndCards();
        if(communityCards.size() > 0) {
            outputCommunityCards();
        }
        curr->giveActions();
        curr = curr->next;
    }
}


//  S   E   T   T   E   R   S   &
//  G   E   T   T   E   R   S

/*static*/ void Dealer::outputCommunityCards() {
    cout << setw(30) << "Community cards:  "
         << left << setw(20) << Dealer::communityCards[0].toString() << "\n" << right;
    for(int i = 1; i < Dealer::communityCards.size(); i++) {
        cout << setw(30) << " " << Dealer::communityCards[i].toString() << "\n";
    }
}

/*static*/ void Dealer::addToPool(int num) {
    Dealer::pool += num;
}
/*static*/ void Dealer::setMinBet(int num) {
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



