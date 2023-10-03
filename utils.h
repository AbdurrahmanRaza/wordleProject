#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <iostream>
#include <fstream>

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

#endif