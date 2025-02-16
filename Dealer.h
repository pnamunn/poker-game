#include "Card.h"
#include "PlayerList.h"
#include "Deck.h"

#ifndef DEALER_H
#define DEALER_H

// TODO make singleton?

// Class used to carry out the game functions
// Class of static datamembers to facilitate program-wide shared data
class Dealer {
    private:
        static int pot;
        static int minBet;
        static int roundMin;    // Call value for this round.  Raises must be above this value.
        
    public:
        // Card cards[5];
        static vector<Card> communityCards;
        static int totalPlayerCount;
        static bool allOthersAllInOrFoldedFlag;
        static bool allOthersFoldedFlag;


        /* Default Constructor */
        Dealer();

        /* Determine which Player acts as Dealer for this round, and consequently
        which Players are posting the small & big blind this round. */
        static void determineDealer(PlayerList &inPlayers);

        /* Prompts Player after Dealer to post small blind. */
        static void smallBlind(bool big);

        /* Deal hole cards to each Players in PlayerList. */
        static void dealHoleCards(PlayerList &inPlayers, Deck &deck);

        /* Reveal a community card. */
        static void flipCard();

        /* Give all eligible players their actions. */
        static void giveActions(PlayerList& inPlayers, bool preFlop=false);


        /* Go thru list of players, showing them their info,
        and prompting them for an action. */
        static void goAroundTheTable(PlayerList &players);

        /* Pre-betting phase where first player sets small blind,
        second player sets big blind, and remaining players 
        go around the table. */
        //static void preflopRound(bool useBlinds, PlayerList &players);


        //  S   E   T   T   E   R   S   &
        //  G   E   T   T   E   R   S

        static void outputCommunityCards();

        static void addToPot(int num);
        static const int getPotValue();

        static void setMinBet(int num);
        static const int getMinBet();

        static void setRoundMin(int num);
        static const int getRoundMin();

};

#endif