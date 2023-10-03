#include <cctype>
#include <iostream>
#include <string>

using namespace std;

#include "utils.h"

int main(int argc, char* argv[]) {

    // TODO: Select this word randomly from words.txt
    string solution = selectRandomWord();

    string attempt;
    int numAttempts = 0;

    while ((numAttempts < 6)){

        bool validAttempt = true;

        cin >> attempt;

        if (attempt.length() != 5) {
            validAttempt = false;
            cout << "Input is wrong length, try again" << endl;
        }

        if (validAttempt){
            for (int i = 0; i < attempt.length(); i++){
                if (!isalpha(attempt[i])) {
                    validAttempt = false;
                    cout << "Only input letters, try again" << endl;
                    break;
                }
                else {
                    attempt[i] = tolower(attempt[i]);
                }
            }
        }

        if (validAttempt){
            if (!wordIsAllowed(attempt)){
                validAttempt = false;
                cout << "Word is not allowed, try again" << endl;
            }
        }

        // TODO: Check if attempt is in allowed.txt

        if (validAttempt) {
            numAttempts++;
            cout << numAttempts << ". ";

            for (int i = 0; i < 5; i++){
                if (attempt[i] == solution[i]){
                    //solution[i] = '-';
                    cout << green(attempt[i]) << " ";
                }
                else if (contains(attempt[i], solution) != -1) {
                    //solution[contains(attempt[i], solution)] = '-';
                    cout << yellow(attempt[i]) << " ";
                }
                else {
                    cout << gray(attempt[i]) << " ";
                }
            }
            cout << endl;
        }

        if (attempt == solution) break;

    }

    return 0;
}