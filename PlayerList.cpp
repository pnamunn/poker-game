#include "PlayerList.h"
#include "Player.h"
#include <iostream>
#include <cmath>
using namespace std;


PlayerList::PlayerList(PlayerList *outOfGameList) {
    this->outOfGame = outOfGameList;
}


// PlayerList::PlayerList(PlayerList &copyTarget) {
//     head = new Player;
//     *head = *(copyTarget.head);

//     tail = new Player;
//     *tail = *(copyTarget.tail);

//     length = copyTarget.length;
// }


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
    // (returning pointer to preceeding player)
Player* PlayerList::removePlayer(string name) {
    Player *curr = head;
    Player* preceedingPlayer = NULL;
    bool found = false;
    do {
        if(curr->name == name) {
            if(curr == head) {  // if removing head of list
                if((head->next == head) && (head->last == head)) {  // if only one player left in list
                    head = NULL;
                    found = true;
                    preceedingPlayer = NULL;    // no preceeding
                    break;
                }
                else {
                    head = curr->next;  // next in line becomes head
                }
            }
            
            preceedingPlayer = curr->last;
            (curr->last)->next = curr->next;
            (curr->next)->last = curr->last;
            found = true;
            break;
        }
        curr = curr->next;
    } while(curr != head);
    // cout << "sucessfully removed from inlist";

    if(found) {
        if(outOfGame != NULL) {   // if the outOfGame list is being used
            outOfGame->addPlayer(*curr);  // add player to outList
            // cout << "Player '" << name << "' removed and placed in outList.\n";
        }
        else {
            // cout << "Player '" << name << "' removed.\n";
        }
    }
    else {
        cerr << "Error: Cannot remove.  Player name '" << name << "' not found.\n";
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

