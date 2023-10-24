#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

#include "utils.h"

int main(int argc, char* argv[]) {

    // planning to use for keyboard display
    

    //string solution = selectRandomWord();
    string solution = "stare";

    string attempt;
    int numAttempts = 0;

    vector<int> greenPos;
    vector<int> yellowPos;

    bool won = false;

    while ((numAttempts < 6)){

        cin >> attempt;

        if (attempt == "TERMINATE") return 0; // for debug
        if (attempt == "MAP") printMap(getLettersMap()); // for debug

        bool validAttempt = validifyAttempt(attempt);

        if (validAttempt) {
            numAttempts++;
            cout << numAttempts << ". ";
            checkAttempt(attempt, solution, greenPos);
        }

        if (attempt == solution) {
            cout << "You got it! The word is " << solution << endl;
            won = true;
            break;
        }

    }

    if (!won) cout << "Game over! The word is " << solution << endl;

    ofstream file;
    file.open("stats.txt", ios::app);
    if (file.is_open()){
        file << solution << " " << won << " " << numAttempts << endl;
    }

    return 0;
}