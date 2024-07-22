#include "Player.h"
#include "PlayerList.h"
#include "Card.h"
#include "Dealer.h"
#include "helpers.h"
#include <iostream>
using namespace std;




Player::Player() {}

void Player::placeBet(int num) {
    if(num < this->chips) {        // Player doesn't bet all their chips
        // cout << this->name << " bets " << num << "\n";
        Dealer::addToPool(num);
        this->chips -= num;
    }
    else {      // Player goes all in
        // cout << this->name << " goes all in with " << this->chips << "\n";
        Dealer::addToPool(this->chips);
        this->chips = 0;
    }
}

void Player::fold(Player &player) {     // sit out the game
    // outPlayers.addPlayer(player);
    // inPlayers.removePlayer(player->name);
    cout << player.name << " folds\n";
}


void Player::check(Player &player) {    // avoid betting, only available if no one has bet this round
    cout << player.name << " checks\n";
}

void Player::call(Player &player) {     // match previous bet
    // if(player->chips > minBet) {
    //     cout << player->name << " calls " << minBet << "\n";
    //     placeBet(minBet, minBet);
    // }
    // else {
    //     cout << player->name << " calls & goes all-in with their " << player->chips << "\n";
    //     placeBet(player->chips, 0, player);
    // }
}

void Player::raise(Player &player) {    // choose to double the betting minimum, or more
    // int raiseNum;
    // cout << "Choose how much to raise, between " << minBet << " to " << player->chips << " :\n";
    // cin >> raiseNum;
    // if(raiseNum < player->chips) {
    //     cout << player->name << " raises to " << raiseNum << "\n";
    //     placeBet(minBet, minBet, player);
    //     placeBet(minBet, minBet, player);
    // }
}

void Player::showHand(Player &player) {
    // for(int i=0; i<2; i++) {
    //     cout << player->cards[0] << " " << player->cards[1];   TODO create a template for << for Card class type
    // }
}


void Player::checkForceAllIn(int threshold, string moveName, Player &player) {
}



//  H   E   L   P   E   R   S

void Player::turnHeader() {
    clearConsole();
    cout << "\t\t\t\t\t***** FOR " << this->name << "'s EYES ONLY *****\n\n";
    cout << "\t\t\t\t\t press enter to display your info -> ";
    cin.ignore(1000, '\n');

}


void Player::turnPrompt(PlayerList &inPlayers, bool preflop/*=0*/) {
    clearConsole();

    cout << "\t\t\t\t\t***** FOR " << this->name << "'s EYES ONLY *****\n\n";
    cout << "\t Chips: " << this->chips << "\n";
    cout << "\t Cards: " << this->cards[0].getValueName() << " of " << this->cards[0].getSuitName()
         << "\t\t" << this->cards[1].getValueName() << " of " << this->cards[1].getSuitName() << "\n\n";

    char action;
    bool inputErrorFlag;

    do {
        inputErrorFlag = 0;

        if(preflop == 1) {
            cout << "\t\t\t\t\t Choose to (c)all " << Dealer::getRoundMin() << " chips, (r)aise, or (f)old: ";
        }
        else {
            cout << "\t\t\t\t\t Choose to check(t), (c)all " << Dealer::getRoundMin() << " chips, (r)aise, or (f)old: ";
        }
        cin >> action;
        cout << "\n";

        switch(action) {
            case 't':   // CHECK
                if(preflop == 0) {
                    cout << "\t\t\t\t You choose to check.\n\n";
                }
                else {
                    cout << "\t\t\t\t\t You can't check in the preflop, try again.\n\n";
                    inputErrorFlag = 1;
                }

            break;

            case 'c':   // CALL
                if(this->chips > Dealer::getRoundMin()) {
                    this->placeBet(Dealer::getRoundMin());
                    cout << "\t\t\t\t\t You called " << Dealer::getRoundMin() << " and have " << this->chips << " chips left.\n";
                }
                else {
                    cout << "\t\t\t\t You call & go all-in with " << this->chips << " chips.  You have " << this->chips << " chips left.\n";
                    placeBet(this->chips);
                }
            break;

            case 'r':   // RAISE
                cout << "\t\t\t\t\t " << "Raise to how much? (>= " << Dealer::getRoundMin() << "): ";
                int raiseVal;
                cin >> raiseVal;

                if(this->chips > raiseVal) {
                    this->placeBet(raiseVal);
                    cout << "\t\t\t\t You raised to " << raiseVal << " and have " << this->chips << " chips left.\n";
                }
                else {
                    cout << "\t\t\t\t You raise & go all-in with " << this->chips << " chips.  You have " << this->chips << " chips left.\n";
                    placeBet(this->chips);
                }
                Dealer::setRoundMin(raiseVal);
            break;

            case 'f':   // FOLD
                cout << "\t\t\t\t You choose to fold with " << this->chips << " chips left.\n\n";
                // TODO take out player
                inPlayers.removePlayer(this->name);
                inPlayers.listPlayers();
            break;

            default:
                cerr << "Not an option, try again.\n\n";
                inputErrorFlag = 1;
            break;
        }

    } while(inputErrorFlag == 1);

    cout << "\t\t\t\t\t press enter to end your turn -> ";
    cin.ignore();   // clear buffer after cin << was used
    cin.ignore(1000, '\n');
    clearConsole();
}



