#include "Player.h"
#include "Card.h"


Player::Player() {}

void Player::modifyPool(int poolAdd, int playerMinus, Player &player) {
    // dealer.pool += poolAdd;
    player.chips -= playerMinus;
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
    //     modifyPool(minBet, minBet, player);
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

void Player::smallBlind(Player &player) {
    // int smallBlind = floor(minBet/2);
    // cout << player->name << " posts the small blind of " << smallBlind << "\n";
    // modifyPool(smallBlind, smallBlind, player);
}

void Player::checkForceAllIn(int threshold, string moveName, Player &player) {
}

void Player::showHand(Player &player) {
    // for(int i=0; i<2; i++) {
    //     cout << player->cards[0] << " " << player->cards[1];   TODO create a template for << for Card class type
    // }
}