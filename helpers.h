#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#ifndef HELPERS_H
#define HELPERS_H

enum conditions {GTE, GT};  // greater than or equal to (>=), greater than (>)

static int errorCheck(int checkVar, conditions condition, int checkVal,
                      string fail_msg) {
    bool inputErrorFlag = true;
    while(inputErrorFlag == true) {
        if(cin.fail()) {
            cin.clear();    // clear fail bit
            // cin.ignore();

            cin.ignore(1000, '\n');     // flush cin buffer
            cout << "Dumbass, that's a letter.  Go again: ";
            cin >> checkVar;
            continue;
        }

        switch(condition) { // print out fail msg if they do not meet the condition & break
            case GTE:
                if(checkVar >= checkVal) {
                    inputErrorFlag = false;
                    break;
                }
                // print fail msg & accept user input again
                cout << fail_msg;
                cin >> checkVar;
            break;

            case GT:
                if(checkVar > checkVal) {
                    inputErrorFlag = false;
                    break;
                }
                cout << fail_msg;
                cin >> checkVar;
            break;
        }

        cout << "\n";
    }
    return checkVar;
}

static void clearConsole() {
    #if _WIN32
        system("cls");
    #elif __unix__ 
        system("clear");
    #endif
}

static void enterToContinue() {
    cout << "\n" << setw(50) << "press enter to continue ->";
    cin.ignore();
    cin.ignore(1000, '\n');
}

#endif