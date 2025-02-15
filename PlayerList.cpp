#include "PlayerList.h"
#include "Player.h"
#include <iostream>
#include <cmath>
#include <variant>
using namespace std;


PlayerList::PlayerList(PlayerList* outOfGameList, PlayerList* allInList) {
    this->outOfGame = outOfGameList;
    this->allIn = allInList;
}

void PlayerList::addPlayer(Player &player, int num/*=0*/) {
    if(num != 0) {      // optional parameter, to be used when Player is new & does not have a name yet
        player.name = "Player" + to_string(num);
    }
    // cout << "entered addPlayer()";
    // cout << "\n head : " << head;
    if(head == NULL) {     // first Player in the list
        // cout << "entered if head == NULL";
        head = &player;
        // cout << "head assign success";
        player.next = &player;
        player.last = &player;
    }
    else {
        if(head->next == head) {    // if adding second item in list
            head->next = &player;
        }
        player.last = head->last;
        (head->last)->next = &player;
        head->last = &player;
        player.next = head;
    }
    // cout << player.name << " added  " << &player << "\n";
}

// TODO redo unit tests to match changed functionality
    // (returning pointer to preceeding player
    // & supporting a variant)
// TODO make this work with either a name arg or a Player& arg
    // make both args optional
    // want to be able to remove current player
Player* PlayerList::removePlayer(PlayerList* dest, variant<Player*, string> player) {
    // bool found = false;
    Player* preceedingPlayer = NULL;
    Player* foundPlayer = NULL;

    // player arg is string datatype, so we'll search for the Player by their name datamember
    if(player.index()) {
        string name = get<string>(player);
        Player* curr = head;
        do {
            if(curr->name == name) {
                if(curr == head) {  // if removing head of list
                    if((head->next == head) && (head->last == head)) {  // if there's only 1 player in the list
                        head = NULL;
                        preceedingPlayer = NULL;    // no preceeding
                        // found = true;
                        foundPlayer = curr;
                        break;
                    }
                    else {
                        head = curr->next;  // next in line becomes head
                    }
                }
                
                preceedingPlayer = curr->last;
                (curr->last)->next = curr->next;
                (curr->next)->last = curr->last;
                // found = true;
                foundPlayer = curr;
                break;
            }
            curr = curr->next;
        } while(curr != head);
    }

    // player arg is Player* datatype, so we'll remove the Player the ptr points to
    else {
        Player* ptr = get<Player*>(player);
        if(ptr == NULL) {
            cerr << "Error: a NULL Player* ptr was passed to removePlayer()\n";
            exit(-1);
        }
        if((ptr == head) && (ptr->last == ptr)) {    // if ptr is the only Player in the list
            head = NULL;
            preceedingPlayer = NULL;
        }
        else {
            if(ptr == head) { head = ptr->next; }
            preceedingPlayer = ptr->last;
            (ptr->last)->next = ptr->next;
            (ptr->next)->last = ptr->last;
        }
        foundPlayer = ptr;
    }

    // Now add the found Player to the desired dest
    if(foundPlayer != NULL) {
        if(dest != NULL) {
            dest->addPlayer(*foundPlayer);
            // cout << "Player '" << name << "' removed and placed in outList.\n";
        }
        else {
            // cout << "Player '" << name << "' removed.\n";
            cerr << "Error: a NULL PlayerList* dest was passed to removePlayer()\n";
            exit(-1);
        }
    }
    else {
        // cerr << "Error: Cannot remove.  Player name '" << name << "' not found.\n";
        cerr << "Error: Cannot remove.  Player not found.\n";
        exit(-1);
    }

    return preceedingPlayer;
}

void PlayerList::listPlayers(bool listOutPlayers/*=0*/) {
    if((head == NULL) && (outOfGame == NULL)) {
         // if both this list & this list's outOfGame list is empty
        cout << "Arrrg list be empty\n";
    }
    else {
        Player *curr = head;
        cout << "Listing players in game...\n";
        do {
            cout << curr->name << "\n";
            curr = curr->next;
        } while(curr != head);
        cout << "\n";

        if((listOutPlayers) && (outOfGame != NULL)) {
            Player *currOutList = outOfGame->head;
            cout << "Listing players out of game...\n";
            do {
                cout << currOutList->name << "\n";
                currOutList = currOutList->next;
            } while(currOutList != outOfGame->head);
            cout << "\n";
        }
    }
}

void PlayerList::changeHead(int nodeNum) {
    int count = 0;
    Player *curr = head;
    while(count != nodeNum-1) {
        curr = curr->next;
        count++;
    }
    // cout << "\ncurr is on " << curr->name;
    head = curr;
}

int PlayerList::getLength() {
    if(head == NULL) {
        return 0;
    }
    else {
        int count = 1;
        Player *curr = head;
        Player *last = head->last;
        while(curr != last) {
            count++;
            curr = curr->next;
        }
        return count;
    }
}

