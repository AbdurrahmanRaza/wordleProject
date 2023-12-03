#include <cstdlib>
#include <iostream>
#include <igloo/igloo.h>
#include <vector>
#include <fstream>

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "utils.h"
#include "game.h"

using namespace igloo;

std::string exec(std::string command) {
   char buffer[128];
   std::string result = "";

   // Open pipe to file
   FILE* pipe = popen((command + " 2>&1").c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   result.erase(result.find_last_not_of(" \t\n\r\f\v") + 1);
   
   return result;
}

Context(TODO){
    
    Spec(test_game_win_one_attempt_house){
        std::string result = "";
        
        playWordle("house", {"house"});
        system("clear");
        std::vector<std::string> vec = getAttemptedWordsInLatestGame();
        result += "{";
        for (int i = 0; i < vec.size(); i++){
            result += vec[i];
            if (i < vec.size() - 1) result += ", ";
        }
        result += "}";

        std::string expected = "{";
        expected += green('h') + " ";
        expected += green('o') + " ";
        expected += green('u') + " ";
        expected += green('s') + " ";
        expected += green('e') + " ";
        expected +="}";

        Assert::That(result, Equals(expected));
    }

    Spec(test_game_win_few_attempts_stale){
        std::string result = "";
        
        playWordle("stale", {"house", "snake", "state", "stale"});
        system("clear");
        std::vector<std::string> vec = getAttemptedWordsInLatestGame();
        result += "{";
        for (int i = 0; i < vec.size(); i++){
            result += vec[i];
            if (i < vec.size() - 1) result += ", ";
        }
        result += "}";

        std::string expected = "{";
        expected += gray('h') + " ";
        expected += gray('o') + " ";
        expected += gray('u') + " ";
        expected += yellow('s') + " ";
        expected += green('e') + " , ";

        expected += green('s') + " ";
        expected += gray('n') + " ";
        expected += green('a') + " ";
        expected += gray('k') + " ";
        expected += green('e') + " , ";

        expected += green('s') + " ";
        expected += green('t') + " ";
        expected += green('a') + " ";
        expected += gray('t') + " ";
        expected += green('e') + " , ";

        expected += green('s') + " ";
        expected += green('t') + " ";
        expected += green('a') + " ";
        expected += green('l') + " ";
        expected += green('e') + " ";
        expected +="}";

        Assert::That(result, Equals(expected));
    }

    Spec(test_game_lose_bully){
        std::string result = "";
        
        playWordle("bully", {"house", "house", "house", "house", "house", "house"});
        system("clear");
        std::vector<std::string> vec = getAttemptedWordsInLatestGame();
        result += "{";
        for (int i = 0; i < vec.size(); i++){
            result += vec[i];
            if (i < vec.size() - 1) result += ", ";
        }
        result += "}";

        std::string expected = "{";
        for (int i = 0; i < 6; i++){
            expected += gray('h') + " ";
            expected += gray('o') + " ";
            expected += yellow('u') + " ";
            expected += gray('s') + " ";
            expected += gray('e') + " ";
            if (i < 5) expected += ", ";
        }
        expected +="}";

        Assert::That(result, Equals(expected));
    }

    Spec(stats_reset){
        resetStats(false);
        std::vector<std::string> result = {};
        std::ifstream file;
        file.open("stats.txt");
        if (file.is_open()){
            std::string line;
            while(std::getline(file, line)){
                result.push_back(line);
            }
        }
        file.close();
        std::vector<std::string> expected = {};
        Assert::That(result, Equals(expected));
    }

    Spec(stats_works_as_intended){
        resetStats(false);
        playWordle("stale", {"house", "snake", "state", "stale"});
        playWordle("bully", {"house", "house", "house", "house", "house", "house"});

        std::vector<std::string> result = {};
        std::ifstream file;
        file.open("stats.txt");
        if (file.is_open()){
            std::string line;
            while(std::getline(file, line)){
                result.push_back(line);
            }
        }
        file.close();
        std::vector<std::string> expected = {"stale 1 4", "bully 0 6"};
        Assert::That(result, Equals(expected));
    }

    // Tests below no longer work with the program's current structure

    /*Spec(test_state){
        std::string result = exec("echo state| ./temp");
        std::string expected = "";
        expected += green('s') + " ";
        expected += gray('t') + " ";
        expected += green('a') + " ";
        expected += green('t') + " ";
        expected += green('e') + " ";
        Assert::That(result, Equals(expected));
    }

    Spec(test_stale){
        std::string result = exec("echo stale| ./temp");
        std::string expected = "";
        expected += green('s') + " ";
        expected += yellow('t') + " ";
        expected += green('a') + " ";
        expected += yellow('l') + " ";
        expected += green('e') + " ";
        Assert::That(result, Equals(expected));
    }

    Spec(test_teams){
        std::string result = exec("echo teams| ./temp");
        std::string expected = "";
        expected += yellow('t') + " ";
        expected += yellow('e') + " ";
        expected += green('a') + " ";
        expected += gray('m') + " ";
        expected += yellow('s') + " ";
        Assert::That(result, Equals(expected));
    }*/
};

int main(int argc, const char* argv[]){
    return TestRunner::RunAllTests(argc, argv);
}
