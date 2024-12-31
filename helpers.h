#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#ifndef HELPERS_H
#define HELPERS_H

enum conditions {GTE, GT};  // greater than or equal to (>=), greater than (>)

static int errorCheck(int checkVar, conditions condition, int checkVal,
                      string fail_msg) {
    bool inputErrorFlag = 1;
    do {
        switch(condition) { // print out fail msg if they do not meet the condition & break
            case GTE:
                if(checkVar >= checkVal) {
                    inputErrorFlag = 0;
                    break;
                }
                // print fail msg & accept user input again
                cout << fail_msg;
                cin >> checkVar;
            break;

            case GT:
                if(checkVar > checkVal) {
                    inputErrorFlag = 0;
                    break;
                }
                cout << fail_msg;
                cin >> checkVar;
            break;
        }
        cout << "\n";
    } while(inputErrorFlag == 1);
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