#include "Player.h"
#include <iostream>
using namespace std;


class PlayerList {
    public:
        Player *head = NULL;
        PlayerList *outList = NULL;

        /* Default Constructor */
        PlayerList();

        // /* Deep Copy Constructor.makes a deep copy of another PlayerList instance. */
        // PlayerList(PlayerList &copyTarget);

        /* Constructor that has a PlayerList instance data member within it
        to store Players that you remove from this instance. */
        PlayerList(bool includeOutList);

        /* Add Player to PlayerList instance. */
        void addPlayer(Player &player, int num=0);

        /* Remove Player from PlayerList instance & move it into to it's
        outPlayers PlayerList data member. */
        void removePlayer(string name);

        /* List all Players in the PlayerList instance. */
        void listPlayers();

        /* Deep copies the PlayerList. */
        // PlayerList copyList();

        /* Change the head of the PlayerList.  Used when picking the Dealer for
        the game, and therefore the Player turn order. */
        void changeHead(int nodeNum);


};



