#include "PlayerList.h"
#include "Player.h"
#include <iostream>
#include <cmath>
using namespace std;


PlayerList::PlayerList() {}
PlayerList::PlayerList(PlayerList &copyTarget) {
    head = new Player;
    *head = *(copyTarget.head);

    tail = new Player;
    *tail = *(copyTarget.tail);

    length = copyTarget.length;
}


void PlayerList::addPlayer(Player &player, int num/*=0*/) {
    if(num != 0) {      // optional parameter, to be used when Player is new & does not have a name yet
        player.name = "Player" + to_string(num);
    }
    if(head == NULL) {     // first Player in the list
        head = &player;
        tail = &player;
    }
    else {
        tail->next = &player;    // tail's next = new addition
        player.last = tail;    // new addition's last = tail
        tail = &player;        // new addition becomes new tail
    }

    cout << player.name << " added " << head << " " << tail << "\n";
    length++;
}

void PlayerList::removePlayer(string name, PlayerList &outPlayers) {
    Player *curr = head;
    bool success = 0;
    while(curr != NULL) {
        if(curr->name == name) {
            if(curr->next == NULL) {        // if removing the last player in the list
                curr->last->next = NULL;
            }
            else {
                curr->last->next = curr->next;
                curr->next->last = curr->last;
            }
            outPlayers.addPlayer(*curr);
            cout << name << " out of game\n";
            success = 1;
            length--;
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
        while(curr != NULL) {
            cout << curr->name << " " << curr << "\n";
            curr = curr->next;
        }
    }
}

PlayerList PlayerList::copyList() {
    Player *originalCurr = head;

}

PlayerList PlayerList::changeHead(int nodeNum) {    // TODO improve efficiency
    Player *newHead = NULL;
    int count = 0;
    // PlayerList newList;
    PlayerList newList = *this;     // deep copy constructor
    PlayerList tempList;         // will hold all Players before the chosenPlayer
    Player *curr = head;
    cout << "\n\n";
    // traverse thru PlayerList until you're on node number nodeNum
    while(count != nodeNum - 1) {
        // tempList.addPlayer(*curr);
        cout << "\ntraversing: " << curr->name;
        curr = curr->next;
        count++;
    }
    cout << "\ncurr is on " << curr->name;

    // that node == new head & add in rest of list
    newList.head = curr;
    cout << "\nadding rest of list to new list: ";
    while(curr != NULL) {
        newList.addPlayer(*curr);
        cout << "\ncurr->next is: " << curr->next << "\n";
        curr = curr->next;
    }

    // add players that were before new head
    cout << "head is " << head->name;
    curr = head;
    count = 0;
    while(count != nodeNum - 1) {
        newList.addPlayer(*curr);
        curr = curr->next;
        count++;
    }
    newList.tail->next = NULL;

    return newList;
}
