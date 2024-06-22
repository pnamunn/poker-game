#include <iostream>
#include <vector>
#include <string>
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
        cout << "Full deck created...\n";
    }

    // Card drawRandomCard() {

    // }


    void removeCardFromDeck() {
        // int i = 0;
        // while(i < 52) {
        //     cout << cards[i].suit << " " << cards[i++].value << "\n";
        // }
  
        int random = rand() % 52;
        cout << cards[random].suit << " " << cards[random].value << "\n";
        // cout << random;
    }

};


class Player {
    private:
        Card cards[2];
    public:
        string name;
        int chips;
        Player *next = NULL, *last = NULL;

    /* Constructor */
    Player() {}

    void fold(Player *player) {}
    void call(Player *player) {}
    void raise(Player *player) {}
    void showHand(Player *player) {
        for(int i=0; i<2; i++) {
            // player->showCard();
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

        void addPlayer(int i) {
            Player *player = new Player();
            player->name = "Player" + to_string(i);

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
            cout << player->name << " added\n";
        }

        void removePlayer(string name) {
            Player *curr = head;
            bool success = 0;
            while(curr != NULL) {
                if(curr->name == name) {
                    if(curr->next == NULL) {    // removing the last player in the list
                        curr->last->next = NULL;
                    }
                    else {
                        curr->last->next = curr->next;
                        curr->next->last = curr->last;
                    }
                    // outPlayer.addPlayer(&curr);
                    cout << name << " removed\n";
                    success = 1;
                }
                curr = curr->next;
            }
            if(!success)  cout << "That player name not found\n";
        }

        void listPlayers() {
            if(head == NULL) {
                cout << "Arrrg list be empty\n";
            }
            else {
                Player *curr = head;
                while(curr != NULL) {
                    cout << curr->name << "\n";
                    curr = curr->next;
                }
            }
        }
};


class Dealer {
    Dealer() {}

    Card cards[5];
    int pool;

    // shuffle()
    void flipCard() {
        // Card cardDrawn = Deck.drawRandomCard;
        // Deck.removeCardFromDeck(cardDrawn);
        // cout << 
    }
    // poolTotal()
    // compareHands()
    // void dealCards(PlayerList *head) {
    //     while()
    // }

};


int main() {
    srand(time(NULL));      // seed

    PlayerList inPlayer, outPlayer;
    int numPlayers;
    cout << "Enter number of players: ";
    cin >> numPlayers;

    for (int i=1; i <= numPlayers; i++) {
        inPlayer.addPlayer(i);
    }

    inPlayer.listPlayers();
    inPlayer.removePlayer("Player2");
    cout << "\n-\n";
    inPlayer.listPlayers();
    // cout << "\n-";


    // Deck deck;
    // deck.removeCardFromDeck();

}


// int main() {
//     Dealer dealer;
//     int numPlayers;

//     cout << "Enter number of players: ";
//     cin >> numPlayers;
//     Player *ptr;
//     for (int i=0; i < numPlayers; i++) {
        
//     }

// }