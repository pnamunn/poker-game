#pragma once

#include <string>
using namespace std;


class Card {
    public:
        /* Default Constructor */
        Card();

        enum suits {NullSuit=0, Spades=1, Clovers=2, Diamonds=3, Hearts=4};
        enum values {NullValue=0, Ace=1, Two=2, Three=3, Four=4, Five=5, Six=6, Seven=7, Eight=8, Nine=9, Ten=10, Jack=11, Queen=12, King=13};
        // enum instances are the datamembers
        suits suit;
        values value;

        /* Map enum value to suit name string. */
        string getSuitName();

        /* Map enum value to card value string. */
        string getValueName();

        /* Print in format <ValueName> of <SuitName>. */
        string toString();

};

