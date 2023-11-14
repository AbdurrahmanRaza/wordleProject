#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "utils.h"

#define RESET "\033[0m"
#define GREEN_BG "\033[42;30m"
#define YELLOW_BG "\033[43;30m"
#define GRAY_BG "\033[47;30m"

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
}

void showHowToPlay(){

    system("clear");

    std::cout << "=============================================" << std::endl;
    std::cout << "                 HOW TO PLAY                 " << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "Guess the Wordle in 6 tries." << std::endl;
    std::cout << std::endl;
    std::cout << "HOW TO PLAY:" << std::endl;
    std::cout << "- Each guess must be a valid 5 letter word." << std::endl;
    std::cout << "- The color of the tiles will change to show" << std::endl;
    std::cout << "  you how close your guess was to the word." << std::endl;
    std::cout << std::endl;
    std::cout << "| " << GREEN_BG << "w" << RESET << " e a r y |" << std::endl;
    std::cout << "'w' is in the word and in the correct spot." << std::endl;
    std::cout << std::endl;
    std::cout << "| p " << YELLOW_BG << "i" << RESET << " l l s |" << std::endl;
    std::cout << "'i' is in the word but in the wrong spot." << std::endl;
    std::cout << std::endl;
    std::cout << "| v a g " << GRAY_BG << "u" << RESET << " e |" << std::endl;
    std::cout << "'u' is not in the word in any spot." << std::endl;

    std::cin.ignore();
    std::cout << std::endl << "Press [Enter] to continue: ";
    std::cin.get();

}

#endif