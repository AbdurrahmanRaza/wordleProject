#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include<vector>

#define RESET "\033[0m"
#define GREEN_BG "\033[42;30m"
#define YELLOW_BG "\033[43;30m"
#define GRAY_BG "\033[47;30m"

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

bool contains(std::vector<int> v, int num){
    for (int i = 0; i < v.size(); i++){
        if (num == v[i]) return true;
    }
    return false;
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
    for (int i = 0; i < 5; i++){
        if (attempt[i] == solution[i]){
            //solution[i] = '-';
            std::cout << green(attempt[i]) << " ";
            //greenPos.push_back(i);
        }
        else if (contains(attempt[i], solution) != -1) {
            if (solution[contains(attempt[i], solution)] == attempt[contains(attempt[i], solution)]){
                //solution[contains(attempt[i], solution)] = '-';
                std::cout << gray(attempt[i]) << " ";
            }
            else {
                //solution[contains(attempt[i], solution)] = '-';
                std::cout << yellow(attempt[i]) << " ";
            }
            
        }
        else {
            std::cout << gray(attempt[i]) << " ";
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

    std::cout << std::endl;
}


#endif