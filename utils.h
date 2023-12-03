#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#define RESET "\033[0m"
#define GREEN_BG "\033[42;30m"
#define YELLOW_BG "\033[43;30m"
#define GRAY_BG "\033[47;30m"

std::vector<std::string> allAttemptedWords;

std::map<char, int> lettersMap = { // int guide: 0 is unused, 1 is gray, 2 is yellow, 3 is green
    {'a',0}, {'b',0}, {'c',0}, {'d',0}, {'e',0}, {'f',0}, {'g',0}, {'h',0}, {'i',0}, {'j',0}, {'k',0}, {'l',0}, {'m',0},
    {'n',0}, {'o',0}, {'p',0}, {'q',0}, {'r',0}, {'s',0}, {'t',0}, {'u',0}, {'v',0}, {'w',0}, {'x',0}, {'y',0}, {'z',0}
};

void updateKeyboardTextFile(){
    std::ofstream file;
    file.open("../keyboard/lettersMap.txt", std::ios::out);
    if (file.is_open()){
        for (const auto &pair : lettersMap){
            
            file << pair.first << pair.second << std::endl;
        }
    }
    file.close();
}

void resetKeyboardTextFile(){
    lettersMap = { // int guide: 0 is unused, 1 is gray, 2 is yellow, 3 is green
        {'a',0}, {'b',0}, {'c',0}, {'d',0}, {'e',0}, {'f',0}, {'g',0}, {'h',0}, {'i',0}, {'j',0}, {'k',0}, {'l',0}, {'m',0},
        {'n',0}, {'o',0}, {'p',0}, {'q',0}, {'r',0}, {'s',0}, {'t',0}, {'u',0}, {'v',0}, {'w',0}, {'x',0}, {'y',0}, {'z',0} 
    };
    updateKeyboardTextFile();
}

std::string selectRandomWord(){
    std::ifstream file;
    file.open("words.txt", std::ios::in);
    if (file.is_open()){
        std::string word;
        srand(time(0));
        int index = rand() % 2315 + 1; //hardcoded number of lines in words.txt
        std::cout << "Line number in words.txt (remove for final game): " << index << std::endl;
        for (int i = 0; i < index; i++){
            file >> word;
        }
        file.close();
        return word;
    }
    return "slate";
}

bool wordIsAllowed(std::string userInput){
    std::ifstream file;
    file.open("words.txt", std::ios::in);
    if (file.is_open()){
        std::string word;
        while (file >> word){
            if (word == userInput){
                file.close();
                return true;
            }
        }
        file.close();
    }
    
    file.open("allowed.txt", std::ios::in);
    if (file.is_open()){
        std::string word;
        while (file >> word){
            if (word == userInput){
                file.close();
                return true;
            }
        }
        file.close();
    }

    return false;
}

std::string green(char inputText){
    std::string s = "";
    s.push_back(inputText);
    return GREEN_BG + s + RESET;
}

std::string yellow(char inputText){
    std::string s = "";
    s.push_back(inputText);
    return YELLOW_BG + s + RESET;
}

std::string gray(char inputText){
    std::string s = "";
    s.push_back(inputText);
    return GRAY_BG + s + RESET;
}

int contains(char character, std::string word){
    for (int i = 0; i < 5; i++){
        if (word[i] == character) return i;
    }
    return -1;
}

bool validifyAttempt(std::string attempt){
    bool validAttempt = true;

    if (attempt.length() != 5) {
        validAttempt = false;
        std::cout << "Input is wrong length, try again" << std::endl;
    }

    if (validAttempt){
        for (int i = 0; i < attempt.length(); i++){
            if (!isalpha(attempt[i])) {
                validAttempt = false;
                std::cout << "Only input letters, try again" << std::endl;
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
            std::cout << "Word is not allowed, try again" << std::endl;
        }
    }

    return validAttempt;
}

void checkAttempt(std::string attempt, std::string solution, std::vector<int> greenPos){
    std::string attemptedWord = "";
    for (int i = 0; i < 5; i++){
        if (attempt[i] == solution[i]){
            //solution[i] = '-';
            //std::cout << green(attempt[i]) << " ";
            attemptedWord += green(attempt[i]) + " ";
            lettersMap[attempt[i]] = 3;
            //greenPos.push_back(i);
        }
        else if (contains(attempt[i], solution) != -1) {
            if (solution[contains(attempt[i], solution)] == attempt[contains(attempt[i], solution)]){
                //solution[contains(attempt[i], solution)] = '-';
                //std::cout << gray(attempt[i]) << " ";
                attemptedWord += gray(attempt[i]) + " ";
            }
            else {
                //solution[contains(attempt[i], solution)] = '-';
                //std::cout << yellow(attempt[i]) << " ";
                attemptedWord += yellow(attempt[i]) + " ";
                if (lettersMap[attempt[i]] < 2) lettersMap[attempt[i]] = 2;
            }
        }
        else {
            //std::cout << gray(attempt[i]) << " ";
            attemptedWord += gray(attempt[i]) + " ";
            if (lettersMap[attempt[i]] < 1) lettersMap[attempt[i]] = 1;
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

    std::cout << attemptedWord;

    allAttemptedWords.push_back(attemptedWord);

    updateKeyboardTextFile();

    std::cout << std::endl;

    
}

void printBoard(){
    system("clear");
    for (int i = 0; i < allAttemptedWords.size(); i++){
        std::cout << "| " << allAttemptedWords[i] << "|" << std::endl << std::endl;
    }
    for (int j = 0; j < 6 - allAttemptedWords.size(); j++){
        std::cout << "|           |" << std::endl << std::endl;
    }
}

void resetBoard(){
    allAttemptedWords.clear();
}

void setLetterInMap(std::map<char, int> &letterMap, char letter, int status){
    std::cout << letterMap[letter] << std::endl;
    letterMap[letter] = status;
    std::cout << letterMap[letter] << std::endl;
}

void printMap(std::map<char, int> m) {
    int count = 0;
    for (const auto &pair : m){
        count++;
        std::cout << pair.first << pair.second << " ";
        if (count == 13) std::cout << std::endl;
        if (count == 26) std::cout << std::endl;
    }
}

#endif