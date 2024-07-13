#include "Dealer.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "PlayerList.h"


Dealer::Dealer() {}

// shuffle()
// poolTotal()
// compareHands()

/*static*/ void Dealer::determineDealer(PlayerList &inPlayers) {
    int chosenPlayer = rand() % (inPlayers.length) + 1;
    cout << chosenPlayer;
    inPlayers = inPlayers.changeHead(chosenPlayer);
    cout << inPlayers.head->name << " is acting as this game's dealer\n";
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
    Player *curr = players.head->next;
    int smallBlind = floor(minBet / 2);

    cout << curr->name << " posts the small blind of " << smallBlind << "\n";
    curr->modifyPool(smallBlind, smallBlind);

    curr = curr->next;
    int bigBlind;

    cout << curr->name << "Choose a big blind value greater or equal to " << bigBlind << ": ";
    cin >> bigBlind;
    cout << curr->name << " posts a big blind of " << bigBlind << "\n";
    curr->modifyPool(bigBlind, bigBlind);

    while(curr != NULL) {
        curr->turnHeader();
        curr->prompt();


    }
}

/*static*/ void Dealer::setPool(int num) {
    pool += num;
}

/*static*/ void Dealer::setMinBet(int num) {
    minBet = num;
}

/*static*/ void Dealer::getMinBet() {
    return minBet;
}



