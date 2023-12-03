#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include "utils.h"

#define RESET "\033[0m"
#define GREEN_BG "\033[42;30m"
#define YELLOW_BG "\033[43;30m"
#define GRAY_BG "\033[47;30m"

extern void resetKeyboardTextFile();

void playWordle(std::string w = selectRandomWord(), std::vector<std::string> testInputs = {}){
    resetBoard();
    std::string solution = w;

    std::string attempt;
    int numAttempts = 0;

    std::vector<int> greenPos;
    std::vector<int> yellowPos;

    bool won = false;
    printBoard();

    bool isTest = false;
    if (testInputs.size() > 0) isTest = true;

    while ((numAttempts < 6)){
        if (isTest) {
            attempt = testInputs[numAttempts];
        }
        else {
            std::cout << "Attempt " << numAttempts+1 << ": ";
            std::cin >> attempt;
        }

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
    file.close();

    if (!isTest) {
        std::cin.ignore();
        std::cout << std::endl << "Press [Enter] to continue: ";
        std::cin.get();
    }

    resetKeyboardTextFile();
}

std::vector<std::string> getAttemptedWordsInLatestGame(){
    return allAttemptedWords;
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

void showStats(){

    system("clear");

    std::vector<std::string> allWords = {};
    std::vector<int> allWins = {};
    std::vector<int> allAttempts = {};

    int timesPlayed = 0;
    int averageAttempts = 0;
    float winPercent = 0.0;
    int currentStreak = 0;
    int longestStreak = 0;

    std::ifstream file;
    file.open("stats.txt");
    if (file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            timesPlayed++;
            
            std::string currentWord = "";
            for (int i = 0; i < 5; i++) { currentWord.push_back(line[i]); }
            allWords.push_back(currentWord);
           
            std::string currentWin; 
            currentWin += line[6];
            allWins.push_back(std::stoi(currentWin));

            std::string currentAttempts; 
            currentAttempts += line[8];
            allAttempts.push_back(std::stoi(currentAttempts));
        }
    }
    file.close();

    if (timesPlayed > 0){
        for (int i = 0; i < timesPlayed; i++){
            averageAttempts += allAttempts[i];
            winPercent += 1.0 * allWins[i];
            if (allWins[i] == 1) currentStreak++;
            else {
                if (currentStreak > longestStreak) longestStreak = currentStreak;
                currentStreak = 0;
            }
        }
        averageAttempts /= timesPlayed;
        winPercent = 100.0 * winPercent / (1.0 * timesPlayed);
        if (currentStreak > longestStreak) longestStreak = currentStreak;
    }

    std::cout << "==========================" << std::endl;
    std::cout << "    STATISTICS SUMMARY    " << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Times Played: " << timesPlayed << std::endl;
    std::cout << "Average Attempts: " << averageAttempts << std::endl;
    std::cout << "Win Percentage: " << std::setprecision(3) << winPercent << "%" << std::endl;
    std::cout << "Current Streak: " << currentStreak << std::endl;
    std::cout << "Longest Streak: " << longestStreak << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "WORD     ATTEMPTS      WIN" << std::endl;
    std::cout << "--------------------------" << std::endl;
    
    for (int i = 0; i < timesPlayed; i++){
        std::string winOrlose;
        if (allWins[i] == 1) winOrlose = "Yes";
        else winOrlose = " No";
        std::cout << allWords[i] << "           " << allAttempts[i] << "      " << winOrlose << std::endl;
    }

    std::cin.ignore();
    std::cout << std::endl << "Press [Enter] to continue: ";
    std::cin.get();
}

void resetStats(bool showStatsAfter = true){
    std::ofstream file;
    file.open("stats.txt", std::ios::out);
    if (file.is_open()){
        file.clear();
    }
    file.close();

    if (showStatsAfter) showStats();
}

#endif