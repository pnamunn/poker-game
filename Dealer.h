#include "Card.h"
#include "PlayerList.h"
#include "Deck.h"

#ifndef DEALER_H
#define DEALER_H


class Dealer {      // class carries out the game functions
    private:
        static int pool;
        static int minBet;

    public:
        Card cards[5];

        /* Default Constructor */
        Dealer();

        /* Determine which Player acts as Dealer for this round, and consequently
        which Players are posting the small & big blind this round. */
        static void determineDealer(PlayerList &inPlayers);

        /* Prompts Player after Dealer to post small blind. */
        static void smallBlind(bool big);

        /* Deal cards to Players in PlayerList instance. */
        static void dealCards(PlayerList &inPlayers, Deck &deck);

        /* Reveal a community card. */
        static void flipCard();

        /*  */
        static void flop();

        static void preflopRound(PlayerList &players);


        //  S   E   T   T   E   R   S   &
        //  G   E   T   T   E   R   S

        static void setPool(int num);

        static void setMinBet(int num);
        static int getMinBet();

};


#endif