#include "PlayerList.h"
#include "Player.h"
#include <iostream>
#include <cmath>
using namespace std;


PlayerList::PlayerList() {}
  
PlayerList::PlayerList(bool includeOutList) {
    if(includeOutList) {
        outList = new PlayerList();     // uses Default Constructor (aka this list does not 
                                        // have another outList list within it)
    }
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
    if(head == NULL) {     // first Player in the list
        head = &player;
        player.next = &player;
        player.last = &player;
        // tail = &player;
    }
    else {
        // tail->next = &player;    // tail's next = new addition
        // player.last = tail;    // new addition's last = tail
        // tail = &player;        // new addition becomes new tail

        if(head->next == head) {    // if adding second item in list
            head->next = &player;
        }
        player.last = head->last;
        (head->last)->next = &player;
        head->last = &player;
        player.next = head;

    }

    cout << player.name << " added " << &player << player.next << player.last << "\n";
    cout << head->next << head->last << "\n";
}

void PlayerList::removePlayer(string name) {
    Player *curr = head;
    Player *last = head->last;
    bool success = 0;
    while(curr != last) {
        if(curr->name == name) {
            // if(curr->next == NULL) {        // if removing the last player in the list
            //     curr->last->next = NULL;
            // }
            // else {
            (curr->last)->next = curr->next;
            (curr->next)->last = curr->last;
            // }

            if(outList != NULL) {   // if outList is being used & is not empty
                outList->addPlayer(*curr);  // add removed player to the outPlayers list
            }   // TODO add error checking statement for if outList == NULL

            cout << name << " out of game\n";
            success = 1;
            break;
        }
        curr = curr->next;
    }
    if(!success)  cout << "That player name not found\n";
}

void PlayerList::listPlayers() {
    if(head == NULL) {
        cout << "Arrrg list be empty\n";
    }
    else {
        Player *curr = head;
        Player* last = head->last;
        while(curr != last) {
            cout << curr->name << " " << curr << "\n";
            curr = curr->next;
        }
        cout << curr->name << " " << curr << "\n";      // print last player in list
    }
}

// PlayerList PlayerList::copyList() {
//     Player *originalCurr = head;

// }

void PlayerList::changeHead(int nodeNum) {    // TODO improve efficiency
    int count = 0;
    Player *curr = head;
    while(count != nodeNum-1) {
        curr = curr->next;
        count++;
    }
    // cout << "\ncurr is on " << curr->name;
    head = curr;


//     Player *newHead = NULL;
//     int count = 0;
//     // PlayerList newList;
//     PlayerList newList = *this;     // deep copy constructor
//     PlayerList tempList;         // will hold all Players before the chosenPlayer
//     Player *curr = head;
//     cout << "\n\n";
//     // traverse thru PlayerList until you're on node number nodeNum
//     while(count != nodeNum - 1) {
//         // tempList.addPlayer(*curr);
//         cout << "\ntraversing: " << curr->name;
//         curr = curr->next;
//         count++;
//     }
//     cout << "\ncurr is on " << curr->name;

//     // that node == new head & add in rest of list
//     newList.head = curr;
//     cout << "\nadding rest of list to new list: ";
//     while(curr != NULL) {
//         newList.addPlayer(*curr);
//         cout << "\ncurr->next is: " << curr->next << "\n";
//         curr = curr->next;
//     }

//     // add players that were before new head
//     cout << "head is " << head->name;
//     curr = head;
//     count = 0;
//     while(count != nodeNum - 1) {
//         newList.addPlayer(*curr);
//         curr = curr->next;
//         count++;
//     }
//     newList.tail->next = NULL;

//     return newList;
}
