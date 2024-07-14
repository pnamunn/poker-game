#include "Player.h"
#include <iostream>
using namespace std;

#ifndef PLAYERLIST_H
#define PLAYERLIST_H


class PlayerList {
    public:
        Player *head = NULL, *tail = NULL;
        int length = 0;

        /* Default Constructor */
        PlayerList();
        /* Deep Copy Constructor.makes a deep copy of another PlayerList instance. */
        PlayerList(PlayerList &copyTarget);

        /* Add Player to PlayerList instance. */
        void addPlayer(Player &player, int num=0);

        /* Remove Player from PlayerList instance.  Stores the removed Player in
        a different PlayerList instance. */
        void removePlayer(string name, PlayerList &outPlayers);

        /* List all Players in the PlayerList instance. */
        void listPlayers();

        /* Deep copies the PlayerList. */
        // PlayerList copyList();

        /* Change the head of the PlayerList.  Used when picking the Dealer for
        the game, and therefore the Player turn order. */
        PlayerList changeHead(int nodeNum);


};




#endif