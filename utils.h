#ifndef UTILS_H
#define UTILS_H

#include <iostream>

#define RESET "\033[0m"
#define GREEN_BG "\033[42;30m"
#define YELLOW_BG "\033[43;30m"
#define GRAY_BG "\033[47;30m"

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