#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "utils.h"

int main(int argc, char* argv[]) {

    //string solution = selectRandomWord();
    string solution = "spurt";

    string attempt;
    int numAttempts = 0;

    vector<int> greenPos;
    vector<int> yellowPos;

    while ((numAttempts < 6)){

        cin >> attempt;

        bool validAttempt = validifyAttempt(attempt);

        if (validAttempt) {
            numAttempts++;
            cout << numAttempts << ". ";
            checkAttempt(attempt, solution, greenPos);
        }

        if (attempt == solution) {
            cout << "You got it! The word is " << solution << endl;
            return 0;
        }

    }

    cout << "Game over! The word is " << solution << endl;

    return 0;
}