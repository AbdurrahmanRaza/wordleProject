#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "utils.h"

void playWordle(){
    resetBoard();
    //string solution = selectRandomWord();
    std::string solution = "stare";

    std::string attempt;
    int numAttempts = 0;

    std::vector<int> greenPos;
    std::vector<int> yellowPos;

    bool won = false;
    printBoard();

    while ((numAttempts < 6)){
        std::cout << "Attempt " << numAttempts+1 << ": ";
        std::cin >> attempt;

        if (attempt == "MAP") printMap(getLettersMap()); // for debug

        bool validAttempt = validifyAttempt(attempt);

        if (validAttempt) {
            numAttempts++;
            checkAttempt(attempt, solution, greenPos);
            printBoard();
        }

        if (attempt == solution) {
            std::cout << "You got it! The word is " << solution << std::endl;
            won = true;
            break;
        }
    }
    
    if (!won) std::cout << "Game over! The word is " << solution << std::endl;

    std::ofstream file;
    file.open("stats.txt", std::ios::app);
    if (file.is_open()){
        file << solution << " " << won << " " << numAttempts << std::endl;
    }

    std::cin.ignore();
    std::cout << std::endl << "Press [Enter] to continue: ";
    std::cin.get();
    std::cin.ignore();
}

#endif