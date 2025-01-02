#include "Card.h"
#include "PlayerList.h"
#include "Deck.h"

#ifndef DEALER_H
#define DEALER_H

// TODO make singleton?
class Dealer {      // class carries out the game functions
    private:
        static int pool;
        static int minBet;
        static int roundMin;    // Call value for this round.  Raises must be above this value.
        
    public:
        // Card cards[5];
        static vector<Card> communityCards;

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

        /* Go thru list of players, showing them their info,
        and prompting them for an action. */
        static void goAroundTheTable(PlayerList &players);

        /* Pre-betting phase where first player sets small blind,
        second player sets big blind, and remaining players 
        go around the table. */
        static void preflopRound(PlayerList &players);


        //  S   E   T   T   E   R   S   &
        //  G   E   T   T   E   R   S

        static void outputCommunityCards();

        static void addToPool(int num);

        static void setMinBet(int num);
        static const int getMinBet();

        static void setRoundMin(int num);
        static const int getRoundMin();

};

#endif