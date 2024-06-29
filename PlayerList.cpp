#include "PlayerList.h"
#include "Player.h"
#include <iostream>
using namespace std;


PlayerList::PlayerList() {}

/* Add Player to PlayerList instance. */
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
}

/* Remove Player from PlayerList instance.  Stores the removed Player in
a different PlayerList instance. */
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
            break;
        }
        curr = curr->next;
    }
    if(!success)  cout << "That player name not found\n";
}

/* List all Players in the PlayerList instance. */
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