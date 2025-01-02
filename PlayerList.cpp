#include "PlayerList.h"
#include "Player.h"
#include <iostream>
#include <cmath>
using namespace std;


PlayerList::PlayerList() {}
  
PlayerList::PlayerList(bool includeOutList) {
    if(includeOutList) {
        PlayerList x;
        outList = &x;
        // cout << "outlist being used.  Head is " << outList->head << "\n";
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

void PlayerList::removePlayer(string name) {
    Player *curr = head;
    bool found = false;

    do {
        if(curr->name == name) {
            if(curr == head) {  // if removing head of list
                if((head->next == head) && (head->last == head)) {  // if only one player left in list
                    head = NULL;
                    found = true;
                    break;
                }
                else {
                    head = curr->next;  // next in line becomes head
                }
            }
            (curr->last)->next = curr->next;
            (curr->next)->last = curr->last;
            found = true;
            break;
        }
        curr = curr->next;
    } while(curr != head);

    if(found) {
        // cout << name << " out of game\n";
        if(outList != NULL) {   // if an outList is being used
                outList->addPlayer(*curr);  // add player to outList
            }
        // TODO if outlist not being used, just erase player from inList
    }
    else {
        cout << "That player name not found\n";
    }
}

void PlayerList::listPlayers() {
    if(head == NULL) {
        cout << "Arrrg list be empty\n";
    }
    else {
        Player *curr = head;
        do {
            cout << curr->name << "\n";
            curr = curr->next;
        } while(curr != head);
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

