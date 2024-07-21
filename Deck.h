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

        /* Returns a random Card from Deck instance and removes it from the deckCards vector. */
        Card drawRandomCard();

        /* Traverses through deckCards vector and prints each Card. */
        void printDeck();

        // friend ostream &operator<<(ostream &output, Card &card);



};
