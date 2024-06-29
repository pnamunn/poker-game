#include "Card.h"

#include <iostream>
#include <vector>
using namespace std;

#ifndef DECK_H
#define DECK_H

class Deck : public Card {
    public:
        vector<Card> deckCards;     // holds cards of the Deck
        
    /* Default Constructor.  Creates a 52 card deck, storing the cards in the
    deckCards vector. */
    Deck();

    /* Returns a random Card from the Deck and removes it from the deckCards vector. */
    Card drawRandomCard();

};

#endif