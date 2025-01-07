// No-limit Texas Hold'em

#ifdef _WIN32
    #include <windows.h>

#elif __unix__              //  TODO test on unix system
    #include <unistd.h>

#endif

#include <iostream>
#include <vector>
#include <string>
#include <string>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std;
#include "Card.h"
#include "Deck.h"
#include "Dealer.h"
#include "Player.h"
#include "PlayerList.h"
#include "helpers.h"


// PlayerList inPlayers, outPlayers;
// Deck deck;


int main() {
    srand(time(NULL));      // seed
    PlayerList outPlayers(NULL);
    PlayerList players(&outPlayers);
    Deck deck;

    int numPlayers;
    cout << "Enter number of players: ";
    cin >> numPlayers;  // TODO error checking for at least 2 players

    bool useBlinds = 0;
    // TODO:
    // cout << "Do you want to use blinds? (y/n): ";
    // cin >> useBlinds;   // TODO error checking


    for (int i=1; i <= numPlayers; i++) {
        Player *player = new Player();
        players.addPlayer(*player, i);
    }
    
    // players.listPlayers();
    // cout << "done listing players";
    // players.removePlayer("Player2");
    // cout << "just removed player2";
    // players.listPlayers(true);
    // cout << "just listed players after moving one to outList";


    Dealer::determineDealer(players);
    Dealer::dealHoleCards(players, deck);
    clearConsole();
    
    // PREFLOP
    Dealer::setMinBet(5);
    // Dealer::preflopRound(players);
    // Dealer::goAroundTheTable(players);    // TODO go thru just the remaining players, & continue until an ante is agreed on


    int agreementCount = 0;
    int inPlayerCount = players.getLength();
    int allInPlayers = 0;
    int ante = 0;
    int raiseVal;
    char action;
    bool inputErrorFlag = false;
    Player *currPlayer = players.head;

    if(useBlinds) {
        // if blinds are used, no checking may occur

        // Small blind
        Player *curr = players.head->next;
        int smallBlind = floor(Dealer::getMinBet() / 2);
        string temp;
        curr->placeBet(smallBlind);
        cout << "\n" << setw(15) << "***** " << curr->name << "'s turn *****"
        // cout << "\t\t\t\t\t press enter to post the small blind of " << smallBlind << " chips -> ";
        // cin.ignore();   // clear buffer after cin >> was used (in getting the number of players in main)
        // cin.ignore(1000, '\n');
            << "\n"
            << "\n" << "You gave the small blind of " << smallBlind
            << "\n" << "You now have " << curr->chips << " chips left.";
        enterToContinue();
        // cout << "\t\t\t\t\t press enter to end your turn -> ";
        // cin.ignore(1000, '\n');
        // do { getline(cin, temp);} while(temp.length() != 0);
        clearConsole();

        // Big blind
        curr = curr->next;
        int bigBlind;
        cout << "\n" << setw(15) << "***** " << curr->name << "'s turn *****"
            << "\n"
            << "\n" << "Chips: " << curr->chips
            << "\n" << "Choose a big blind value to bet (>= " << Dealer::getMinBet() << "): ";
        cin >> bigBlind;
        bigBlind = errorCheck(bigBlind, GTE, Dealer::getMinBet(),
                            ("\t Try again, your big blind has to be >= " + to_string(Dealer::getMinBet()) + ": "));
        Dealer::setRoundMin(bigBlind);
        curr->placeBet(bigBlind);
        cout << "You now have " << curr->chips << " chips left.";
        enterToContinue();
        // cout << "\t\t\t\t\t press enter to end your turn -> ";
        // cin.ignore();   // clear buffer after cin << was used for bigBlind
        // cin.ignore(1000, '\n');
    }
    else {
    // Go around the table until all people agree on the an ante
        // betting continues until every player has either folded,
        // gone all in
        // or matched to ante everyone else has done
    

    // until a bet is made, your options are to
        // check (make no bet) or open (start the betting) or fold
    while(agreementCount != inPlayerCount) {
        // Print header
        cout << "\n" << setw(15) << "***** " << currPlayer->name << "'s turn *****"
         << "\n\n"
         << "Your chips: " << currPlayer->chips
         << setw(15) << " "
         << "The pot: " << Dealer::getPotValue() << "\n";

        // If betting hasn't opened yet, give them these options
        if(ante == 0) {
            // Prompt
            cout << agreementCount << "/" << inPlayerCount
                << " players have agreed on an ante of " << ante << " chips.\n"
                << setw(10) << "Either (c)heck, (o)pen betting, of (f)old: ";

            do {    // do-while loop provides error checking
                cin >> action;
                
                // FSM for checking, opening, folding, or re-prompting
                switch(action) {
                    case 'c':   // CHECK
                        agreementCount++;
                        cout << setw(10) << "You chose to check 0 chips.\n";
                        enterToContinue();
                    break;
                
                    case 'o':       // OPEN BETTING
                        agreementCount = 0;
                        cout << setw(10) << "You open betting with: ";
                        cin >> ante;    // TODO error check that > 0
                        currPlayer->placeBet(ante);
                    break;

                    case 'f':   // FOLD
                        cout << setw(10) << "You chose to fold\n";
                        players.removePlayer(currPlayer->name);
                    break;

                    default:
                        inputErrorFlag = true;
                        cerr << setw(14) <<  "Not an option, try again.\n\n";
                    break;
                }

            } while(inputErrorFlag == true);

            inputErrorFlag = false;     // reset flag
        }

        // after someone opens, your options are
        // fold, call (match highest bet)
        // raise (increase highest bet by this much)

        else {      // else if ante > 0
            // Prompt
            cout << setw(10) << "Either (c)all " << ante << " chips, (r)aise more, or (f)old: ";

            do {    // do-while loop provides error checking
                cin >> action;

                // FSM for calling, raising, folding, or re-prompting
                switch(action) {
                    case 'c':   // CALL
                        agreementCount++;
                        if(currPlayer->chips > ante) {  // can afford to put up that many chips, and some
                            currPlayer->placeBet(ante);
                            cout << setw(10) << "You call " << ante << " and have " << currPlayer->chips << " chips left.\n";
                        }
                        else {
                            cout << setw(10) << "You call & go all-in with " << currPlayer->chips << " chips.  You have " << currPlayer->chips << " chips left.\n";
                            currPlayer->placeBet(currPlayer->chips);
                        }
                    break;

                    case 'r':   // RAISE
                        agreementCount = 0;
                        cout << setw(10) << "Raise by how much?: ";
                        cin >> raiseVal;
                        raiseVal = errorCheck(raiseVal, GT, 0,
                                              "\t Silly goose, your raise value has to be > 0, or else it's just a call. Try again: ");
                        if(currPlayer->chips > (raiseVal + ante)) {
                            currPlayer->placeBet(raiseVal + ante);
                            cout << setw(10) << "You raise by " << raiseVal << " to bet a " 
                                 << (raiseVal + ante) << " total and have " << currPlayer->chips << " chips left.\n";
                        }
                        else {
                            cout << setw(10) << "You go all-in by raising by " << currPlayer->chips << " chips.  You have " << currPlayer->chips << " chips left.\n";
                            currPlayer->placeBet(currPlayer->chips);
                        }

                    break;

                    case 'f':   // FOLD
                        cout << setw(10) << "You chose to fold\n";
                        players.removePlayer(currPlayer->name);
                    break;

                    default:
                        cerr << setw(14) <<  "Not an option, try again.\n\n";
                        inputErrorFlag = 1;
                    break;
            }
            } while(inputErrorFlag = true);

            inputErrorFlag = false;     // reset flag
        }

        inPlayerCount = players.getLength();    // re-evaluate how many players are still in
        
        // all other players folded, so players.head wins the pot
        if(inPlayerCount == 1) {
            cout << players.head->name << "wins bc everyone else wussed out";
        }

    }

    // If you got here, agreementCount == inPlayerCount
    cout << "Goddam, you finally agreed on an ante in the PreFlop, we can move on";
    cout << "You have agreed on the ante of " << ante;
    enterToContinue();

    
    }


    // FLOP

    Dealer::communityCards.push_back(deck.drawRandomCard());
    Dealer::communityCards.push_back(deck.drawRandomCard());
    Dealer::communityCards.push_back(deck.drawRandomCard());
    clearConsole();
    cout << setw(15) << "** You made it to the Flop! **\n"
         << "The first 3 community cards are:\n   " 
         << Dealer::communityCards[0].toString() << "\n   "
         << Dealer::communityCards[1].toString() << "\n   "
         << Dealer::communityCards[2].toString();
    enterToContinue();
    
    Dealer::goAroundTheTable(players);

    // TURN
    Dealer::communityCards.push_back(deck.drawRandomCard());
    clearConsole();
    cout << setw(15) << "** Hey, you're at the Turn! **\n"
         << "The next community card is:\n   " 
         << Dealer::communityCards[3].toString();
    enterToContinue();

    Dealer::goAroundTheTable(players);


    // RIVER
    Dealer::communityCards.push_back(deck.drawRandomCard());
    clearConsole();
    cout << setw(15) << "** The last part is the River! **\n"
         << "The last community card is:\n   " 
         << Dealer::communityCards[4].toString();
    enterToContinue();
    Dealer::goAroundTheTable(players);

    // SHOWDOWN
    // TODO is there betting before the showdown?
    clearConsole();
    cout << setw(15) << "** Welcome to the Showdown! **\n";

}

// TODO NEXT: test files needed for Card and Deck
