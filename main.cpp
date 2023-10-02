#include <cctype>
#include <cstdlib>
#include <iostream>

using namespace std;

#define RESET "\033[0m"
#define GREEN_BG "\033[42;30m"
#define YELLOW_BG "\033[43;30m"
#define GRAY_BG "\033[47;30m"

string green(string inputText){
    return GREEN_BG + inputText + RESET;
}

string yellow(string inputText){
    return YELLOW_BG + inputText + RESET;
}

string gray(string inputText){
    return GRAY_BG + inputText + RESET;
}

int main(int argc, char* argv[]) {

    // TODO: Select this word randomly from words.txt
    string solution = "slate";

    string attempt;
    int numAttempts = 0;

    while (attempt != solution || numAttempts != 6){

        bool validAttempt = true;

        cin >> attempt;
        for (char letter : attempt){
            if (!isalpha(letter)) {
                validAttempt = false;
                cout << "Invalid user input.";
                break;
            }
        }

    }
    

    return 0;
}