#pragma once

#include "Player.h"
#include <iostream>
using namespace std;

/*
Circular doubly linked list to make methods like changeHead() and 
Dealer::goAroundTheTable() easier to implement.
*/
class PlayerList {
    public:
        Player *head = NULL;
        PlayerList *outOfGame = NULL;   // if needed, init this to point to another list

        /* Default Constructor */
        PlayerList(PlayerList *outOfGameList);

        // /* Deep Copy Constructor.makes a deep copy of another PlayerList instance. */
        // PlayerList(PlayerList &copyTarget);

        /* Add Player to the end of the PlayerList linked list. */
        void addPlayer(Player &player, int num=0);

        /* Remove Player from PlayerList linked list.
        If the outOfGame datamember has been init'ed, adds it onto that list.
        Returns pointer to Player before the removed Player. */
        Player* removePlayer(string name);

        /* List all Players in the PlayerList instance. */
        void listPlayers(bool listOutPlayers=0);

        /* Deep copies the PlayerList. */
        // PlayerList copyList();

        /* Change the head of the PlayerList.  Used when picking the Dealer for
        the game, and therefore the Player turn order. */
        void changeHead(int nodeNum);

        /* Returns number of Players in PlayerList. */
        int getLength();



};



