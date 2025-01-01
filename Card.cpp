#include "Card.h"
#include <iostream>
#include <string>
using namespace std;


Card::Card() {
    enum suits suit = NullSuit;
    enum values value = NullValue;
}

enum suits {NullSuit=0, Spades=1, Clovers=2, Diamonds=3, Hearts=4};
enum values {NullValue=0, Ace=1, Two=2, Three=3, Four=4, Five=5, Six=6, Seven=7, Eight=8, Nine=9, Ten=10, Jack=11, Queen=12, King=13};
suits suit;
values value;

string Card::getSuitName() {
    // TODO create an exception type for if NULL card & make try/catch block
    switch(suit) {
        case Spades:
            return "Spades";
        case Clovers:
            return "Clovers";
        case Diamonds:
            return "Diamonds";
        case Hearts:
            return "Hearts";
        case NullSuit:
            cerr << "Error: Trying to access a Card.suit datamember that's uninitiated";
            exit(-1);
        default:
            cout << "Error when trying to getSuitName()\n"
                 << "Card.suit val did not map to a valid enum";
            exit(-1);
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
        case NullValue:
            cerr << "Error: Trying to access a Card.value datamember that's uninitiated";
            exit(-1);
        default:
            cout << "Error when trying to getValueName()\n"
                 << "Card.value val did not map to a valid enum";
            exit(-1);
    }
}

string Card::toString() {
    return this->getValueName() + " of " + this->getSuitName();
}
