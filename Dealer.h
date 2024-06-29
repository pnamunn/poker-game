#include "Card.h"

#ifndef DEALER_H
#define DEALER_H

class Dealer {
    public:
        /* Default Constructor */
        Dealer();

        Card cards[5];
        int pool = 0;

        /* Determine which Player acts as Dealer for this round, and consequently
        which Players are posting the small & big blind this round. */
        static void determineDealer();

        /*  */
        static void blind(bool big);

        /* Deal cards to Players in PlayerList instance. */
        static void dealCards(PlayerList &inPlayers, Deck &deck);

        /* Reveal a community card. */
        static void flipCard();

        /*  */
        static void flop();

};

#endif