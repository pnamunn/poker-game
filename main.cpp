#include <iostream>
#include <vector>
using namespace std;


class Card {
        public:
            enum suits {Spades, Clovers, Diamonds, Hearts};
            enum values {Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};     // default enum values assigned are correct
            suits suit;
            values value;

        Card() {}

};


class Deck : public Card {
    public:
        vector<Card> cards;     // holds cards of the Deck
        
    /* Construct Deck */
    Deck() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                Card aCard;
                aCard.suit = static_cast<suits>(i);     // static cast needed for compatibility between enum & int
                aCard.value = static_cast<values>(j);
                cards.push_back(aCard);
            }
        }
        cout << "\n Full deck created...";
    }

    // Card drawRandomCard() {

    // }

    void removeCardFromDeck(Card card) {

    }

};


class Player {
    private:
        Card cards[2];
    public:
        string name;
        int chips;
        Player *next, *last;

    /* Constructor */
    Player() {}

    void prompt(Player *player) {
        int choice;
        cout << player->name << "'s turn: \n";
        cin >> choice;
        switch(choice) {
            case 0:
                fold();
            case 1:
                call();
            case 2:
                raise();
            default:
                cout << "Not an option, try again";
        }
    }

    void fold(Player *player) {}
    void call(Player *player) {}
    void raise(Player *player) {}
    void showHand(Player *player) {
        for(int i=0; i<2; i++) {
            // player->showCard();
        }
    }
};


class PlayerList {
    Player *head, *tail, *curr;

    void addPlayer(Player *ptr) {}
    void removePlayer(Player* ptr) {}
};


class Dealer {
    Dealer() {}

    Card cards[5];
    int pool;

    // shuffle()
    void flipCard() {
        Card cardDrawn = Deck.drawRandomCard;
        Deck.removeCardFromDeck(cardDrawn);
        cout << 
    }
    // poolTotal()
    // compareHands()

};


int main() {
    // cout << "Hello";
    PlayerList inPlayer, outPlayer;
    Deck deck;

}


// int main() {
//     Dealer dealer;
//     int numPlayers = 0;

//     cout << "Enter number of players: ";
//     cin >> numPlayers;
//     Player *ptr;
//     for (int i=0; i < numPlayers; i++) {
        
//     }

// }