#pragma once

#include "Player.h"
#include <iostream>
#include <variant>
using namespace std;

/*
Circular doubly linked list to make methods like changeHead() and 
Dealer::goAroundTheTable() easier to implement.
*/
class PlayerList {
    public:
        Player *head = NULL;
        PlayerList *outOfGame = NULL;   // points to a list for holding all Players who are out (folded or lost all their chips)
        PlayerList *allIn = NULL;   // points to a list for holding all Players who have gone all-in

        /* Default Constructor.
        Must initiate the outOfGame & allIn datamembers to point to something. */
        PlayerList(PlayerList *outOfGameList, PlayerList* allInList);

        /* Add Player to the end of the PlayerList linked list. */
        void addPlayer(Player &player, int num=0);

        /* Remove Player from PlayerList linked list and move it to the
        given dest (either the outOfGame list or the allIn list).
        Indicate which Player you want to remove by giving either a ptr or
        the name datamember.
        Returns pointer to Player before the removed Player. */
        Player* removePlayer(PlayerList* dest, variant<Player*, string> player);

        /* List all Players in the PlayerList instance. */
        void listPlayers(bool listOutPlayers=0);

        /* Add Player to all-in list. 
        All-in players are deprived of actions for the rest of the game
        and only show back up in the Showdown. */
        void addToAllInList(Player &player);

        /* Change the head of the PlayerList.  Used when picking the Dealer for
        the game, and therefore the Player turn order. */
        void changeHead(int nodeNum);

        /* Returns number of Players in PlayerList. */
        int getLength();



};



