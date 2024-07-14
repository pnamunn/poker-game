#include "Deck.h"
#include "Card.h"
// #include <iostream>
// using namespace std;

    
Deck::Deck() {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 13; j++) {
            Card aCard;
            aCard.suit = static_cast<suits>(i);     // static cast needed for compatibility between enum & int
            aCard.value = static_cast<values>(j);
            deckCards.push_back(aCard);
        }
    }
    cout << "Full deck created...\n";
}

Card Deck::drawRandomCard() {
    // int i = 0;
    // while(i < 52) {
    //     cout << cards[i].suit << " " << cards[i++].value << "\n";
    // }
    int random = rand() % 52;
    cout << deckCards[random].suit << " " << deckCards[random].value << "\n";
    // Card drawnCard = deckCards[random];
    deckCards.erase(deckCards.begin() + random);
    // cout << "card removed from deck\n";

    return deckCards[random];
}

void Deck::printDeck() {
    // vector<Card>::iterator itr;
    // for(auto itr = deckCards.begin(); itr != deckCards.end(); itr++) {
    //     cout << *itr << "/n";
    // }
    cout << "Printing deck: \n";
    for(Card &card : deckCards) {
        cout << card.getSuitName() << ", ";
        cout << card.getValueName() << "\n";
    }

    
}

// ostream &operator<<(ostream &output, Card &card) {
//     output << card << "/n";
//     return output;
// }
