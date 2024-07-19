#include <string>
#include <iostream>
using namespace std;

#ifndef HELPERS_H
#define HELPERS_H


static int errorCheck(int checkVar, int checkVal, string fail_msg) {
    bool inputErrorFlag;
    do {
        inputErrorFlag = 0;
        if(checkVar >= checkVal) {  // break so you can move on to success code
            break;
        }
        else {      // print fail msg & accept user input again
            inputErrorFlag = 1;
            cout << fail_msg;
            cin >> checkVar;
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

#endif