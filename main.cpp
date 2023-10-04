#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "utils.h"

int main(int argc, char* argv[]) {

    // TODO: Select this word randomly from words.txt
    //string solution = selectRandomWord();
    string solution = "slate";

    string attempt;
    int numAttempts = 0;

    vector<int> greenPos;
    vector<int> yellowPos;

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
                    greenPos.push_back(i);
                }
                else if (contains(attempt[i], solution) != -1) {
                    if (solution[contains(attempt[i], solution)] == attempt[contains(attempt[i], solution)]){
                        //solution[contains(attempt[i], solution)] = '-';
                        cout << gray(attempt[i]) << " ";
                    }
                    else {
                        //solution[contains(attempt[i], solution)] = '-';
                        cout << yellow(attempt[i]) << " ";
                    }
                    
                }
                else {
                    cout << gray(attempt[i]) << " ";
                }
            }

            /*for (int i = 0; i < 5; i++){
                if (contains(attempt[i], solution) != -1){
                    yellowPos.push_back(i);
                }
            }
            for (int i = 0; i < greenPos.size(); i++){
                cout << greenPos[i] << ", ";
            }
            for (int i = 0; i < yellowPos.size(); i++){
                cout << yellowPos[i] << ", ";
            }*/

            cout << endl;
        }

        if (attempt == solution) {
            cout << "You got it! The word is " << solution << endl;
            return 0;
        }

    }

    cout << "Game over! The word is " << solution << endl;

    return 0;
}