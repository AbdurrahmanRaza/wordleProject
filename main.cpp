#include <iostream>
#include <string>

using namespace std;

#include "utils.h"

int main(int argc, char* argv[]) {

    // TODO: Select this word randomly from words.txt
    string solution = "slate";

    string attempt;
    int numAttempts = 0;

    while ((attempt != solution) && (numAttempts < 6)){

        bool validAttempt = true;

        cin >> attempt;

        if (attempt.length() != 5) {
            validAttempt = false;
            cout << "Invalid user input." << endl;
        }

        for (char letter : attempt){
            if (!isalpha(letter)) {
                validAttempt = false;
                cout << "Invalid user input." << endl;
                break;
            }
        }

        // TODO: Check if attempt is in allowed.txt

        if (validAttempt) {
            numAttempts++;
            cout << numAttempts << ". ";

            for (int i = 0; i < 5; i++){
                if (attempt[i] == solution[i]){
                    solution[i] = '-';
                    cout << green(attempt[i]) << " ";
                }
                else if (contains(attempt[i], solution) != -1) {
                    solution[contains(attempt[i], solution)] = '-';
                    cout << yellow(attempt[i]) << " ";
                }
                else {
                    cout << gray(attempt[i]) << " ";
                }
            }
            cout << endl;
        }

    }

    return 0;
}