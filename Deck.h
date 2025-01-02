#pragma once

#include "Card.h"
#include <iostream>
#include <vector>
using namespace std;


class Deck : public Card {
    public:
        vector<Card> deckCards;     // holds cards of the Deck
        
        /* Default Constructor.  Creates a 52 card deck, storing the cards in the
        deckCards vector. */
        Deck();

        /* Picks a random card from the deckCards vector, erases it from the
        vector, and returns the Card object instance. */
        Card drawRandomCard();

        /* Traverses through deckCards vector and prints each Card. */
        void printDeck();

        // friend ostream &operator<<(ostream &output, Card &card);



};
