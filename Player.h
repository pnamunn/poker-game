#include "Card.h"
#include <iostream>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H


class Player {
    public:
        Card cards[2];
        string name;
        int chips = 100;
        Player *next = NULL, *last = NULL;

        /* Default Constructor */
        Player();

        /* Modify pool value & Player's chips value after they bet. */
        void placeBet(int num);

        /* Player forfeits this round of the game. */
        void fold(Player &player);

        /* Player avoids betting.  Only available if no one has bet this round. */
        void check(Player &player);

        /* Player matches the previous bet. */
        void call(Player &player);

        /* Player chooses to double the betting minimum, or more. */
        void raise(Player &player);


        /* Player reveals their cards. */
        void showHand(Player &player);


        //  H    E   L   P   E   R   S

        /* Check if Player does not have enough chips for the bet
        and is forced to go all-in. */
        void checkForceAllIn(int threshold, string moveName, Player &player);

        /* Indicate which Player's confidential info is about to be showed. */
        void turnHeader();


        void prompt();

        static void clearConsole();


};


#endif