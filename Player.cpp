#include "Player.h"
#include "Card.h"
#include "Dealer.h"


Player::Player() {}

void Player::modifyPool(int poolAdd, int playerMinus/*=NULL*/) {
    if(playerMinus <= this->chips) {
        cout << player->name << " raises to " << raiseNum << "\n";

    }


    Dealer::setPool(poolAdd);
    if(raiseNum < player->chips) {
        cout << player->name << " raises to " << raiseNum << "\n";
        modifyPool(minBet, minBet, player);
    }
    this->chips -= playerMinus;
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
    //     modifyPool(minBet, minBet);
    // }
    // else {
    //     cout << player->name << " calls & goes all-in with their " << player->chips << "\n";
    //     modifyPool(player->chips, 0, player);
    // }
}

void Player::raise(Player &player) {    // choose to double the betting minimum, or more
    // int raiseNum;
    // cout << "Choose how much to raise, between " << minBet << " to " << player->chips << " :\n";
    // cin >> raiseNum;
    // if(raiseNum < player->chips) {
    //     cout << player->name << " raises to " << raiseNum << "\n";
    //     modifyPool(minBet, minBet, player);
    // }
}

void Player::showHand(Player &player) {
    // for(int i=0; i<2; i++) {
    //     cout << player->cards[0] << " " << player->cards[1];   TODO create a template for << for Card class type
    // }
}


void Player::checkForceAllIn(int threshold, string moveName, Player &player) {



void clearConsole() {
    #if _WIN32
        system("cls");
    #elif __unix__ 
        system("clear");
    #endif
}

// Helper
void Player::turnHeader() {
    clearConsole();
    cout << "***** FOR " << this->name << "'S EYES ONLY *****\n\n\n";
    cout << "\t\t press enter to display your info ->";
    cin >> "";    
}


void Player::prompt() {
    clearConsole();
    cout << "***** FOR " << this->name << "'S EYES ONLY *****\n\n\n";
    cout << "\t Chips: " << this->chips << "\n";
    cout << "\t Cards: " << this->cards << "\n";

    char action;
    cout << "\t\t now (c)all " << Dealer::getMinBet() << ", (r)aise, or (f)old: ";
    cin >> action;      // TODO error checking
    cout << "\n";

    switch(action) {
        case 'c':
            if(this->chips > Dealer::getMinBet()) {
                cout << " You called " << Dealer::getMinBet() << "\n";
                this->modifyPool(Dealer::getMinBet(), Dealer::getMinBet());
            }
            else {
                cout << "You call & go all-in with " << player->chips << " chips\n";
                modifyPool(player->chips, player->chips);
            }
        default:
            cerr << "Error with Player::prompt() action switch case";
    }


}