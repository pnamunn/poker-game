// No-limit Texas Hold'em

#ifdef _WIN32
    #include <windows.h>

#elif __unix__              //  TODO test on unix system
    #include <unistd.h>

#endif

#include <iostream>
#include <vector>
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
    numPlayers = errorCheck(numPlayers, GT, 1,
                            "You need more than 1 live player to participate. Try again: ");
                           

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


    // Dealer::setMinBet(5);
    // Dealer::preflopRound(players);
    // Dealer::goAroundTheTable(players);    // TODO go thru just the remaining players, & continue until an ante is agreed on

    int ante = 0;   // have to reset to 0 at the beginning of each round
    int bet;
    int raiseVal;
    char action;
    bool inputErrorFlag = false;
    // TODO player doesn't get any more action prompts if they decided to go all-in
    // TODO skip to Showdown if all players are all-in
    int allInPlayers = 0;

    // Player *currPlayer = players.head->next;    // the person after the dealer gets the first action turn
    

    // PRE-FLOP
    int agreementCount = 0;
    int inPlayerCount = players.getLength();
    Player *currPlayer = players.head;

    
    if(useBlinds) {
        // if blinds are used, no checking may occur

        // Small blind
        // Player *curr = players.head->next;
        int smallBlind = floor(Dealer::getMinBet() / 2);
        string temp;
        currPlayer->placeBet(smallBlind);
        cout << "\n" << setw(15) << "***** " << currPlayer->name << "'s turn *****"
        // cout << "\t\t\t\t\t press enter to post the small blind of " << smallBlind << " chips -> ";
        // cin.ignore();   // clear buffer after cin >> was used (in getting the number of players in main)
        // cin.ignore(1000, '\n');
            << "\n"
            << "\n" << "You gave the small blind of " << smallBlind
            << "\n" << "You now have " << currPlayer->chips << " chips left.";
        enterToContinue();
        // cout << "\t\t\t\t\t press enter to end your turn -> ";
        // cin.ignore(1000, '\n');
        // do { getline(cin, temp);} while(temp.length() != 0);
        clearConsole();

        // Big blind
        currPlayer = currPlayer->next;
        int bigBlind;
        cout << "\n" << setw(15) << "***** " << currPlayer->name << "'s turn *****"
            << "\n"
            << "\n" << "Chips: " << currPlayer->chips
            << "\n" << "Choose a big blind value to bet (>= " << Dealer::getMinBet() << "): ";
        cin >> bigBlind;
        bigBlind = errorCheck(bigBlind, GTE, Dealer::getMinBet(),
                            ("\t Try again, your big blind has to be >= " + to_string(Dealer::getMinBet()) + ": "));
        Dealer::setRoundMin(bigBlind);
        currPlayer->placeBet(bigBlind);
        cout << "You now have " << currPlayer->chips << " chips left.";
        enterToContinue();
        // cout << "\t\t\t\t\t press enter to end your turn -> ";
        // cin.ignore();   // clear buffer after cin << was used for bigBlind
        // cin.ignore(1000, '\n');
    }
    else {  // don't use blinds
    // Go around the table until all people agree on the an ante
        // betting continues until every player has either folded,
        // gone all in,
        // or matched to the ante everyone else has done
    

    // until a bet is made, your options are to
        // check (make no bet) or open (start the betting) or fold
        while(agreementCount != inPlayerCount) {
            currPlayer = currPlayer->next;  // move on to next player
            inputErrorFlag = false;

            // Print header
            cout << "\n" << setw(15) << "***** " << currPlayer->name << "'s turn *****"
            << "\n\n"
            << "Your chips: " << currPlayer->chips
            << setw(15) << " "
            << "The pot: " << Dealer::getPotValue() << "\n\n";

            cout << agreementCount << "/" << inPlayerCount
                    << " players have agreed on an ante of " << ante << " chips.\n\n";

            // If betting hasn't opened yet, give them these options
            if(ante == 0) {

                inputErrorFlag = false;
                do {    // do-while loop provides error checking
                    inputErrorFlag = false;

                    // Prompt
                    cout << setw(10) << "Either (c)heck, (o)pen betting, or (f)old: ";
                    cin >> action;
                    
                    // FSM for checking, opening, folding, or re-prompting
                    switch(action) {
                        case 'c':   // CHECK
                            cout << setw(10) << "You chose to check 0 chips.\n";
                            agreementCount++;
                        break;
                    
                        case 'o':   // OPEN BETTING
                            cout << setw(10) << "You open betting with: ";
                            cin >> bet;
                            bet = errorCheck(bet, GT, 0,
                                            "\t Open with more than 0, or else it's just a check. Try again: ");
                            
                            if(currPlayer->chips > bet) {  // can afford to put up that many chips, and some
                                currPlayer->placeBet(bet);
                                cout << setw(10) << "You open using " << bet << " chips and have " << currPlayer->chips << " chips left.\n";
                                ante = bet;
                            }
                            else {
                                cout << setw(10) << "You open by going all-in with " << currPlayer->chips << " chips.\n";
                                currPlayer->placeBet(currPlayer->chips);
                                ante = currPlayer->chips;
                            }
                            agreementCount = 1;
                        break;

                        case 'f':   // FOLD
                            cout << setw(10) << "You chose to fold.\n";
                            // remove the current player & then have currPlayer point to the player before the removed player
                            currPlayer = players.removePlayer(currPlayer->name);
                        break;

                        default:
                            inputErrorFlag = true;
                            cerr << setw(14) <<  "Not an option, try again.\n\n";
                        break;
                    }

                } while(inputErrorFlag == true);

                enterToContinue();

                // inputErrorFlag = false;     // reset flag
            }

            // after someone opens, your options are
            // fold, call (match highest bet),
            // or raise (increase highest bet by this much)

            else {      // else if ante != 0
               
                inputErrorFlag = false;
                do {    // do-while loop provides error checking
                    inputErrorFlag = false;

                    // Prompt
                    cout << setw(10) << "Either (c)all " << ante << " chips, (r)aise more, or (f)old: ";
                    cin >> action;

                    // FSM for calling, raising, folding, or re-prompting
                    switch(action) {
                        case 'c':   // CALL
                            if(currPlayer->chips > ante) {  // can afford to put up that many chips, and some
                                currPlayer->placeBet(ante);
                                cout << setw(10) << "You call " << ante << " and have " << currPlayer->chips << " chips left.\n";
                            }
                            else {
                                cout << setw(10) << "You call & go all-in with " << currPlayer->chips << " chips.\n";
                                currPlayer->placeBet(currPlayer->chips);
                            }
                            agreementCount++;
                        break;

                        case 'r':   // RAISE
                            cout << setw(10) << "Raise by how much?: ";
                            cin >> raiseVal;
                            raiseVal = errorCheck(raiseVal, GT, 0,
                                                "Silly goose, your raise value has to be > 0, or else it's just a call. Try again: ");
                           
                            bet = raiseVal + ante;
                            if(currPlayer->chips > bet) {
                                currPlayer->placeBet(bet);
                                cout << setw(10) << "You raise the ante of " << ante << " by " << raiseVal << ", putting in " 
                                    << bet << " chips.  You now have " << currPlayer->chips << " chips left.\n";
                                ante = bet;
                            }
                            else {
                                cout << setw(10) << "Trying to raise the ante by " << raiseVal << "chips, you go all-in with " << currPlayer->chips << " chips.\n";
                                ante = currPlayer->chips;
                                currPlayer->placeBet(currPlayer->chips);
                            }
                            agreementCount = 1;
                        break;

                        case 'f':   // FOLD
                            cout << setw(10) << "You chose to fold.\n";
                            // remove the current player & then have currPlayer point to the player before the removed player
                            currPlayer = players.removePlayer(currPlayer->name);
                        break;

                        default:
                            cerr << setw(14) <<  "Not an option, try again.\n\n";
                            inputErrorFlag = true;
                        break;
                    }

                } while(inputErrorFlag == true);

                enterToContinue();
                inputErrorFlag = false;     // reset flag
            }

            inPlayerCount = players.getLength();    // re-evaluate how many players are still in
            
            // all other players folded, so players.head wins the pot
            if(inPlayerCount == 1) {
                cout << players.head->name << " wins bc everyone else wussed out/n";
                exit(1);    // TODO change to instead move on to another game
            }
        } // end while(agreementCount != inPlayerCount) loop

        // If you got here, agreementCount == inPlayerCount
        cout << "\nGoddamm, you finally agreed on an ante in the PreFlop, we can move on...\n";
        cout << "Everyone agreed on the ante of " << ante << "\n";
        enterToContinue();
    }


    // FLOP
    ante = 0;
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
