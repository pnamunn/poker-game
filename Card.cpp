#include "Card.h"
#include <iostream>
#include <string>
using namespace std;


Card::Card() {}

enum suits {Spades=1, Clovers=2, Diamonds=3, Hearts=4};
enum values {Ace=1, Two=2, Three=3, Four=4, Five=5, Six=6, Seven=7, Eight=8, Nine=9, Ten=10, Jack=11, Queen=12, King=13};
suits suit;
values value;

string Card::getSuitName() {
    switch(suit) {
        case Spades:
            return "Spades";
        case Clovers:
            return "Clovers";
        case Diamonds:
            return "Diamonds";
        case Hearts:
            return "Hearts";
        default:
            return "getSuitName() error";
    }
}

string Card::getValueName() {
    switch(value) {
        case Ace:
            return "Ace";
        case Two:
            return "Two";
        case Three:
            return "Three";
        case Four:
            return "Four";
        case Five:
            return "Five";
        case Six:
            return "Six";
        case Seven:
            return "Seven";
        case Eight:
            return "Eight";
        case Nine:
            return "Nine";
        case Ten:
            return "Ten";
        case Jack:
            return "Jack";
        case Queen:
            return "Queen";
        case King:
            return "King";
        default:
            return "getValueName() error";
    }
}

string Card::toString() {
    return this->getValueName() + " of " + this->getSuitName();
}
