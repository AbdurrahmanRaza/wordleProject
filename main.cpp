#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

#include "game.h"

int main(int argc, char* argv[]) {
    resetKeyboardTextFile();
    system("clear");
    while (true){
        cout << "=========================" << endl;
        cout << "    WELCOME TO WORDLE    " << endl;
        cout << "========================="  << endl;
        cout << endl;
        cout << "1. Play Wordle" << endl;
        cout << "2. How to Play" << endl;
        cout << "3. Statistics Summary" << endl;
        cout << "4. Reset Statistics" << endl;
        cout << "5. Exit" << endl;
        cout << endl;
        cout << "Select an option: ";
        string menuOption = "0";
        cin >> menuOption;

        if (menuOption == "1") playWordle();
        else if (menuOption == "2") showHowToPlay();
        else if (menuOption == "3") showStats();
        else if (menuOption == "4") resetStats();
        else if (menuOption == "5") break;
        system("clear");
    }

    return 0;
}