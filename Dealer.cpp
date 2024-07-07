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
}

/*static*/ void Dealer::blind(bool big) {
    if(!big) {      // small blind
    }
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