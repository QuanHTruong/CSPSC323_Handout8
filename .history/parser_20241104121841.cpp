// parse.cpp

#include "Grammar.h"
#include <iostream>

int main() {
    Grammar grammar;
    grammar.initializeProduction("CFG.txt");  // Load CFG from file

    grammar.computeFirstSets();
    grammar.computeFollowSets();

    std::cout << "FIRST Sets:\n";
    grammar.printFirstSets();

    std::cout << "\nFOLLOW Sets:\n";
    grammar.printFollowSets();

    return 0;
}