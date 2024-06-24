#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Card;
class Player;
class PlayerList;
class Deck;
class Dealer;


class Card {
   public:
       enum suits {Spades=1, Clovers=2, Diamonds=3, Hearts=4};
       enum values {Ace=1, Two=2, Three=3, Four=4, Five=5, Six=6, Seven=7, Eight=8, Nine=9, Ten=10, Jack=11, Queen=12, King=13};
       suits suit;
       values value;

       string getSuitName() {
           switch(suit) {
               case Spades:
                   return "Spades";
               case Clovers:
                   return "Clovers";
               case Diamonds:
                   return "Diamonds";
               case Hearts:
                   return "Hearts";
           }
       }

        string getValueName() {
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
            }
        }

   Card() {}

};


class Player {
    private:
        Card cards[2];
    public:
        Card cards[2];
        string name;
        int chips;
        Player *next = NULL, *last = NULL;

    /* Constructor */
    Player() {}

    void fold(Player *player) {
        outPlayers.addPlayer(player);
        inPlayers.removePlayer(player->name);
        cout << player->name << " folded";
    }

    void call(Player *player) {}
    void raise(Player *player) {}

    void showHand(Player *player) {
        for(int i=0; i<2; i++) {
            // cout << player->cards[0] << " " << player->cards[1];   TODO create a template for << for Card class type
        }
    }

    // void prompt(Player *player) {
    //     int choice;
    //     cout << player->name << "'s turn:\n";
    //     cin >> choice;
    //     switch(choice) {
    //         case 0:
    //             player.fold();
    //         case 1:
    //             call();
    //         case 2:
    //             raise();
    //         default:
    //             cout << "Not an option, try again";
    //             prompt(player);
    //     }
    // }

};


class PlayerList {
    public:
        Player *head = NULL, *tail = NULL;
        int length = 0;
    
    public:
        void addPlayer(Player *player, int num=0) {
            // Player *player = new Player();
            if(num != 0) {      // optional parameter
                player->name = "Player" + to_string(num);
            }

            if(head == NULL) {     // first Player in the list
                head = player;
                tail = player;
            }
            else {
                // Player *temp = tail;
                tail->next = player;    // tail's next = new addition
                player->last = tail;    // new addition's last = tail
                tail = player;        // new addition becomes new tail
            }
            cout << player->name << " added " << head << " " << tail << "\n";
            ++length;
        }

        void removePlayer(string name) {
            Player *curr = head;
            bool success = 0;
            while(curr != NULL) {
                if(curr->name == name) {
                    if(curr->next == NULL) {    // removing the last player in the list
                    if(curr->next == NULL) {        // removing the last player in the list
                        curr->last->next = NULL;
                    }
                    else {
                        curr->last->next = curr->next;
                        curr->next->last = curr->last;
                    }
                    // outPlayers.takePlayerOutGame(curr);
                    cout << name << " out of game\n";
                    success = 1;
                }
                curr = curr->next;
            }
            if(!success)  cout << "That player name not found\n";
            --length;
        }

        void listPlayers() {
            if(head == NULL) {
                cout << "Arrrg list be empty\n";
            }
            else {
                Player *curr = head;
                while(curr != NULL) {
                    cout << curr->name << " " << curr << "\n";
                    curr = curr->next;
                }
            }
        }

        int getLength() {
            return length;
        }
};

// Globals
PlayerList inPlayers, outPlayers;

class Deck : public Card {
    public:
        vector<Card> deckCards;     // holds cards of the Deck
        
    /* Construct Deck */
    Deck() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                Card aCard;
                aCard.suit = static_cast<suits>(i);     // static cast needed for compatibility between enum & int
                aCard.value = static_cast<values>(j);
                deckCards.push_back(aCard);
            }
        }
        cout << "Full deck created...\n";
    }

    Card drawRandomCard() {
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

};

Deck deck;


class Dealer {
    public:
    Dealer() {}

    Card cards[5];
    int pool = 0;

    // shuffle()
    static void flipCard() {
        // Card cardDrawn = Deck.drawRandomCard;
        // Deck.removeCardFromDeck(cardDrawn);
        // cout << 
    }
    // poolTotal()
    // compareHands()

    static void dealCards() {
        Player *curr = inPlayers.head;
        while(curr != NULL) {
            cout << "Dealing cards to " << curr->name << "...\n";
            curr->cards[0] = deck.drawRandomCard();
            curr->cards[1] = deck.drawRandomCard();

            // TODO remove cards from deck
            
            cout << curr->cards[0].getSuitName() << ", " << curr->cards[0].getValueName() << "\t" 
                << curr->cards[1].getSuitName() << ", " << curr->cards[1].getValueName() << "\n"; 
            curr = curr->next;
        }
    }

};




int main() {
    srand(time(NULL));      // seed

    int numPlayers;
    cout << "Enter number of players: ";
    cin >> numPlayers;

    for (int i=1; i <= numPlayers; i++) {
        Player *player = new Player();
        inPlayers.addPlayer(player, i);
    }


    inPlayers.listPlayers();
    
    
    // Dealer::dealCards();
    


}