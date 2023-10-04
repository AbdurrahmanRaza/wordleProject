#include <igloo/igloo.h>

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "utils.h"

using namespace igloo;

Context(TODO){
    /*
        your test cases here
    */

    /*

    Test for:
    - if word is 5 letters long
    - characters in word are all letters
    - if inputted word is even actually a word
    - 

    */

    Spec(test_state){
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
        std::string result = exec("echo state| ./temp");
        std::string expected = "";
        expected += green('s') + " ";
        expected += yellow('t') + " ";
        expected += green('a') + " ";
        expected += yellow('l') + " ";
        expected += green('e') + " ";
        Assert::That(result, Equals(expected));
    }

    Spec(test_teams){
        std::string result = exec("echo state| ./temp");
        std::string expected = "";
        expected += yellow('t') + " ";
        expected += yellow('e') + " ";
        expected += green('a') + " ";
        expected += gray('m') + " ";
        expected += yellow('s') + " ";
        Assert::That(result, Equals(expected));
    }
};

int main(int argc, const char* argv[]){
    return TestRunner::RunAllTests(argc, argv);
}
