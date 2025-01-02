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


// TODO refactor all force-all-in checks with this
void Player::checkForceAllIn(int threshold, string moveName, Player &player) {
}


//  S   E   T   T   E   R   S   &
//  G   E   T   T   E   R   S

void Player::outputChipsAndCards() {
    cout << setw(15) << "***** For " << this->name << "'s eyes only *****\n";

    cout << "\n" << "Chips: " << left << setw(5) << this->chips
         << right << setw(18) << "Your cards:  "
         << left << this->cards[0].toString()
         << "\n" << setw(30) << " "     // adds spacing
         << this->cards[1].toString() << "\n"
         << right;  // reset to default right
}



//  H   E   L   P   E   R   S

// void Player::turnHeader() {
//     clearConsole();
//     cout << setw(15) << "***** For " << this->name << "'s eyes only *****\n";
//     enterToContinue();
//     // cout << "\t\t\t\t\t press enter to display your info -> ";
//     // cin.ignore(1000, '\n');

// }




void Player::giveActions(bool preflop/*=0*/) {
    // clearConsole();
    // cout << setw(15) << "***** For " << this->name << "'s eyes only *****\n";
    // outputChipsAndCards();
    char action;
    bool inputErrorFlag;    // when 1, will prompt user for input again
    do {
        inputErrorFlag = 0;
        if(preflop == 1) {
            cout << setw(10) << "Either (c)all " << Dealer::getRoundMin() << " chips, (r)aise, or (f)old: ";
        }
        else {
            cout << setw(10) << "Either check(t), (c)all " << Dealer::getRoundMin() << " chips, (r)aise, or (f)old: ";
        }
        cin >> action;
        // cout << "\n";

        switch(action) {
            case 't':   // CHECK
                if(preflop == 0) {
                    cout << setw(10) << "You chose to check.\n";
                }
                else {
                    cout << setw(10) << "You can't check in the preflop, try again.\n";
                    inputErrorFlag = 1;
                }
            break;

            case 'c':   // CALL
                if(this->chips > Dealer::getRoundMin()) {
                    this->placeBet(Dealer::getRoundMin());
                    cout << setw(10) << "You call " << Dealer::getRoundMin() << " and have " << this->chips << " chips left.\n";
                }
                else {
                    cout << setw(10) << "You call & go all-in with " << this->chips << " chips.  You have " << this->chips << " chips left.\n";
                    placeBet(this->chips);
                }
            break;

            case 'r':   // RAISE
                cout << setw(10) << "Raise to how much? (> " << Dealer::getRoundMin() << "): ";
                int raiseVal;
                cin >> raiseVal;
                raiseVal = errorCheck(raiseVal, GT, Dealer::getRoundMin(),
                            ("\t Try again, your raise has to be > " + to_string(Dealer::getRoundMin()) + ": "));
                if(this->chips > raiseVal) {
                    this->placeBet(raiseVal);
                    cout << setw(10) << "You raise to " << raiseVal << " and have " << this->chips << " chips left.\n";
                }
                else {
                    cout << setw(10) << "You raise & go all-in with " << this->chips << " chips.  You have " << this->chips << " chips left.\n";
                    placeBet(this->chips);
                }
                Dealer::setRoundMin(raiseVal);
            break;

            case 'f':   // FOLD
                cout << setw(10) << "You chose to fold with " << this->chips << " chips left.\n";
                // TODO take out player
                // inPlayers.removePlayer(this->name);
                // inPlayers.listPlayers();
            break;

            // case '^C':
            //     exit(1);
            // break;

            default:
                cerr << setw(14) <<  "Not an option, try again.\n\n";
                inputErrorFlag = 1;
            break;
        }

    } while(inputErrorFlag == 1);

    cout << "\n" << setw(50) << "press enter to end your turn ->";
    cin.ignore();   // clear buffer after cin << was used
    cin.ignore(1000, '\n');
    clearConsole();
}



