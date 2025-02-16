#include "Dealer.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "PlayerList.h"
#include "helpers.h"
#include "math.h"


Dealer::Dealer() {}

// Init static data members
int Dealer::pot = 0;
int Dealer::minBet, Dealer::roundMin = 5;

vector<Card> Dealer::communityCards;

int Dealer::totalPlayerCount = 0;

bool Dealer::allOthersAllInOrFoldedFlag = false;
bool Dealer::allOthersFoldedFlag = false;



/*static*/ void Dealer::determineDealer(PlayerList &inPlayers) {
    int chosenPlayer = rand() % (inPlayers.getLength()) + 1;     // range [1, inPlayer's length]
    // // cout << chosenPlayer;
    inPlayers.changeHead(chosenPlayer);
    cout << "* " << inPlayers.head->name << " will act as this game's dealer *";
    enterToContinue();
}

/*static*/ void Dealer::giveActions(PlayerList& inPlayers, bool preFlop/*=false*/) {

    // for preflop, break condition should be 
    // once agreementCount == players.getLength()

    // for all other rounds, break condition should be
    // once currPlayer == head->last (all players got one turn)

    // while break condition not met { }

    Player* currPlayer = inPlayers.head;
    bool breakCondition;
    int agreementCount = 0;
    int ante = 0;   // has to be reset to 0 before each round
    int bet;
    int raiseVal;
    char action;
    bool inputErrorFlag = false;


    // Go around the table until all people agree on the an ante
        // betting continues until every player has either folded,
        // gone all in,
        // or matched to the ante everyone else has done

    // TODO delete superfluous inputErrorFlag == false statements in this while loop

    
    do {
        
        currPlayer = currPlayer->next;  // move on to next player
        inputErrorFlag = false;

        // Print player header
        cout << "\n" << setw(15) << "***** " << currPlayer->name << "'s turn *****"
        << "\n\n"
        << "Your chips: " << currPlayer->chips
        << setw(15) << " "
        << "The pot: " << Dealer::getPotValue() << "\n\n";

        if(preFlop && !Dealer::allOthersAllInOrFoldedFlag) {
            cout << agreementCount << "/" << inPlayers.getLength()
                 << " players have agreed on an ante of " << ante << " chips.\n\n";
        }


        if(Dealer::allOthersAllInOrFoldedFlag) {
            inputErrorFlag = false;
            do {    // do-while loop format provides error checking // TODO change to just a while loop
                inputErrorFlag = false;
                // Print prompt
                cout << "You are the last player left after all other players have either folded or went all-in.\n"
                     << "This will be your last action before the Showdown.\n\n"
                     << "Either put up a (b)et of any amount or (f)old: ";
                cin >> action;
                
                // FSM for betting any amount, folding, or re-prompting
                switch(action) {
                    case 'b':   // BET
                        cout << setw(10) << "You're able to bet any amount [0 to all-in].  How much would you like to bet?: ";
                        cin >> bet;
                        if(currPlayer->chips > bet) {  // can afford to put up that many chips, and some
                            currPlayer->placeBet(bet);
                            cout << setw(10) << "You bet " << bet << " chips and have " << currPlayer->chips << " chips left.\n";
                            ante = bet;
                        }
                        else {
                            cout << setw(10) << "You decide to go all-in with " << currPlayer->chips << " chips.\n";
                            ante = currPlayer->chips;
                            currPlayer->placeBet(currPlayer->chips);
                            currPlayer = inPlayers.removePlayer(inPlayers.allIn, currPlayer->name);
                        }
                    break;
                    case 'f':   // FOLD
                        cout << setw(10) << "You chose to fold.\n";
                        // remove the current player & then have currPlayer point to the preceeding player
                        currPlayer = inPlayers.removePlayer(inPlayers.outOfGame, currPlayer->name);
                    break;
                    default:
                        inputErrorFlag = true;
                        cerr << setw(14) <<  "Not an option, try again.\n\n";
                    break;
                }
            } while(inputErrorFlag == true);
            break;  // last player in just had their final action, so break out of the do-while loop
        }



        // Before an opening bet gets made, your options are to
        // check (make no bet), open (start the betting), or fold
        if(ante == 0) {
            inputErrorFlag = false;
            do {    // do-while loop format provides error checking // TODO change to just a while loop
                inputErrorFlag = false;
                // Print prompt
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
                            cout << setw(10) << "What an open.  You open by going all-in with " << currPlayer->chips << " chips.\n";
                            ante = currPlayer->chips;
                            currPlayer->placeBet(currPlayer->chips);
                            currPlayer = inPlayers.removePlayer(inPlayers.allIn, currPlayer->name);
                        }
                        agreementCount = 1;
                    break;
                    case 'f':   // FOLD
                        cout << setw(10) << "You chose to fold.\n";
                        // remove the current player & then have currPlayer point to the preceeding player
                        currPlayer = inPlayers.removePlayer(inPlayers.outOfGame, currPlayer->name);
                    break;
                    default:
                        inputErrorFlag = true;
                        cerr << setw(14) <<  "Not an option, try again.\n\n";
                    break;
                }
            } while(inputErrorFlag == true);
            // inputErrorFlag = false;
        }

        // After someone had opened, your options are to
        // call (match the highest bet), raise (increase highest bet by this much), or fold
        else {  // if ante != 0
            inputErrorFlag = false;
            do {    // do-while loop format provides error checking
                inputErrorFlag = false;
                // Print prompt
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
                            currPlayer = inPlayers.removePlayer(inPlayers.allIn, currPlayer->name);
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
                            cout << setw(10) << "Trying to raise the ante by " << raiseVal << " chips, you go all-in with " << currPlayer->chips << " chips.\n";
                            ante = currPlayer->chips;
                            currPlayer->placeBet(currPlayer->chips);
                            currPlayer = inPlayers.removePlayer(inPlayers.allIn, currPlayer->name);
                        }
                        agreementCount = 1;
                    break;
                    case 'f':   // FOLD
                        cout << setw(10) << "You chose to fold.\n";
                        // remove the current player & then have currPlayer point to the player before the removed player
                        currPlayer = inPlayers.removePlayer(inPlayers.outOfGame, currPlayer->name);
                    break;
                    default:
                        cerr << setw(14) <<  "Not an option, try again.\n\n";
                        inputErrorFlag = true;
                    break;
                }
            } while(inputErrorFlag == true);
            // inputErrorFlag = false;     // reset flag
        }


        // The last player in should have just gotten their last action, so now exit the do-while loop
        if(Dealer::allOthersAllInOrFoldedFlag) { break; }

        // If there's only 1 player left in, evaluate
        if(inPlayers.getLength() == 1) {
            if(inPlayers.outOfGame->getLength() == (Dealer::totalPlayerCount - 1)) {
                // If all other players have folded, allow no more actions for the rest of the game.
                // Program will go on to announce the winner & show Showdown just for fun.
                Dealer::allOthersFoldedFlag = true;
                // cout << inPlayers.head->name << " wins bc everyone else wussed out\n";
                break;
            }
            else {
                // Else, all other players have gone all-in || some folded and some went all-in
                // Allow the last player in 1 more action & then have program skip to Showdown to determine the winner.
                Dealer::allOthersAllInOrFoldedFlag = true;
            }
        }


        enterToContinue();
        inputErrorFlag = false;     // reset flag


        // Check the break condition again
        if(preFlop) {
            // If in Pre-Flop round, exit the while loop once all players have agreed on the ante.
            // Also accounts for if there are 
            breakCondition = ((agreementCount == inPlayers.getLength()) && (!allOthersAllInOrFoldedFlag));   
        }
        else {
            // In all other rounds, exit the while loop after everyone has their 1 turn
            breakCondition = (currPlayer == inPlayers.head);
        }

    } while(!breakCondition);


    if(preFlop && !Dealer::allOthersAllInOrFoldedFlag) {
        cout << "\n\nGoddamm, you finally agreed on an ante in the Pre-Flop, we can move on...\n";
        cout << "Everyone agreed on the ante of " << ante << "\n";
    }
}


/*static*/ void Dealer::dealHoleCards(PlayerList &inPlayers, Deck &deck) {
    Player *curr = inPlayers.head;
    do {
        // cout << "Dealing cards to " << curr->name << "...\n";
        curr->cards[0] = deck.drawRandomCard();
        curr->cards[1] = deck.drawRandomCard();
        curr = curr->next;
    } while(curr != inPlayers.head);
    
}

// /*static*/ void Dealer::flipCard() {
//     Card communityCard = Deck::drawRandomCard();
//     Deck.removeCardFromDeck(cardDrawn);
//     // cout << 
// }

// /*static*/ void Dealer::preflopRound(bool useBlinds, PlayerList &inPlayers) {
//     if(useBlinds) {
//     // Small blind
//     Player *curr = inPlayers.head->next;
//     int smallBlind = floor(Dealer::getMinBet() / 2);
//     string temp;
//     curr->placeBet(smallBlind);
//     cout << "\n" << setw(15) << "***** " << curr->name << "'s turn *****"
//     // cout << "\t\t\t\t\t press enter to post the small blind of " << smallBlind << " chips -> ";
//     // cin.ignore();   // clear buffer after cin >> was used (in getting the number of players in main)
//     // cin.ignore(1000, '\n');
//          << "\n"
//          << "\n" << "You gave the small blind of " << smallBlind
//          << "\n" << "You now have " << curr->chips << " chips left.";
//     enterToContinue();
//     // cout << "\t\t\t\t\t press enter to end your turn -> ";
//     // cin.ignore(1000, '\n');
//     // do { getline(cin, temp);} while(temp.length() != 0);
//     clearConsole();

//     // Big blind
//     curr = curr->next;
//     int bigBlind;
//     cout << "\n" << setw(15) << "***** " << curr->name << "'s turn *****"
//          << "\n"
//          << "\n" << "Chips: " << curr->chips
//          << "\n" << "Choose a big blind value to bet (>= " << Dealer::getMinBet() << "): ";
//     cin >> bigBlind;
//     bigBlind = errorCheck(bigBlind, GTE, Dealer::getMinBet(),
//                           ("\t Try again, your big blind has to be >= " + to_string(Dealer::getMinBet()) + ": "));
//     Dealer::setRoundMin(bigBlind);
//     curr->placeBet(bigBlind);
//     cout << "You now have " << curr->chips << " chips left.";
//     enterToContinue();
//     // cout << "\t\t\t\t\t press enter to end your turn -> ";
//     // cin.ignore();   // clear buffer after cin << was used for bigBlind
//     // cin.ignore(1000, '\n');
//     }

//     // Go around the table until all people agree on the the ante
//     // Dealer::goAroundTheTable();
//     Player *curr = inPlayers.head;
//
// }

/*static*/ void Dealer::goAroundTheTable(PlayerList &inPlayers) {
    Player *curr = inPlayers.head;
    do {
        clearConsole();
        cout << setw(15) << "***** For " << curr->name << "'s eyes only *****\n";
        enterToContinue();

        clearConsole();
        curr->outputChipsAndCards();
        if(communityCards.size() > 0) {
            outputCommunityCards();
        }
        curr->giveActions();
        curr = curr->next;
    } while(curr != inPlayers.head);
}


//  S   E   T   T   E   R   S   &
//  G   E   T   T   E   R   S

/*static*/ void Dealer::outputCommunityCards() {
    cout << setw(30) << "Community cards:  "
         << left << setw(20) << Dealer::communityCards[0].toString() << "\n" << right;
    for(int i = 1; i < Dealer::communityCards.size(); i++) {
        cout << setw(30) << " " << Dealer::communityCards[i].toString() << "\n";
    }
}

/*static*/ void Dealer::addToPot(int num) {
    Dealer::pot += num;
}
/*static*/ const int Dealer::getPotValue() {
    return Dealer::pot;
}

/*static*/ void Dealer::setMinBet(int num) {
    Dealer::minBet = num;
}
/*static*/ const int Dealer::getMinBet() {
    return Dealer::minBet;
}
/*static*/ void Dealer::setRoundMin(int num) {
    Dealer::roundMin = num;
}
/*static*/ const int Dealer::getRoundMin() {
    return Dealer::roundMin;
}



