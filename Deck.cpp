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
    // cout << "Full deck created...\n";
}

Card Deck::drawRandomCard() {
    int random = rand() % deckCards.size();
    Card drawnCard = deckCards[random];
    // cout << drawnCard.suit << " " << drawnCard.value << "\n";
    deckCards.erase(deckCards.begin() + random);
    return drawnCard;
}

void Deck::printDeck() {
    // vector<Card>::iterator itr;
    // for(auto itr = deckCards.begin(); itr != deckCards.end(); itr++) {
    //     cout << *itr << "/n";
    // }
    cout << "\nPrinting deck: \n";
    for(Card &card : deckCards) {
        cout << card.getSuitName() << ", ";
        cout << card.getValueName() << "\n";
    }

    
}

// ostream &operator<<(ostream &output, Card &card) {
//     output << card << "/n";
//     return output;
// }
