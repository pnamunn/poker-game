#include "Deck.h"
#include "Card.h"

    
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
    Card drawnCard = deckCards[random];
    // deckCards.erase(random);
    vector<Card>::iterator it;
    for(auto it = deckCards.begin(); it != deckCards.end(); it++) {
        // if(*it == deckCards[random]) {
        //     deckCards.erase(random);
        // }
    }
    return deckCards[random];
}
