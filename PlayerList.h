#include "Player.h"
#include <iostream>
using namespace std;

#ifndef PLAYERLIST_H
#define PLAYERLIST_H


class PlayerList {
    public:
        Player *head = NULL, *tail = NULL;

        /* Default Constructor */
        PlayerList();

        /* Add Player to PlayerList instance. */
        void addPlayer(Player &player, int num=0);

        /* Remove Player from PlayerList instance.  Stores the removed Player in
        a different PlayerList instance. */
        void removePlayer(string name, PlayerList &outPlayers);

        /* List all Players in the PlayerList instance. */
        void listPlayers();

};


#endif