// Grammar.cpp

#include "Grammar.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype> // For isupper

Grammar::Grammar() {}

std::string Grammar::trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

void Grammar::initializeProduction(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        char nonTerminal = line[0];
        std::string production = trim(line.substr(3)); // Skip "->" and trim any whitespace
        productions[nonTerminal].push_back(production);
    }
    file.close();
}

void Grammar::computeFirstSets() {
    bool updated;
    do {
        updated = false;
        for (auto &[nonTerminal, rules] : productions) {
            for (const std::string &rule : rules) {
                for (char symbol : rule) {
                    if (isupper(symbol)) { // Non-terminal
                        bool containsEpsilon = false;
                        for (char ch : firstSets[symbol]) {
                            if (ch == 'ε') containsEpsilon = true;
                            if (firstSets[nonTerminal].insert(ch).second) updated = true;
                        }
                        if (!containsEpsilon) break;
                    } else { // Terminal
                        if (firstSets[nonTerminal].insert(symbol).second) updated = true;
                        break;
                    }
                }
            }
        }
    } while (updated);
}

void Grammar::computeFollowSets() {
    followSets['E'].insert('$'); // Assuming 'E' is the start symbol
    bool updated;
    do {
        updated = false;
        for (auto &[nonTerminal, rules] : productions) {
            for (const std::string &rule : rules) {
                for (int i = 0; i < rule.length(); i++) {
                    char symbol = rule[i];
                    if (isupper(symbol)) { // Only for non-terminals
                        std::set<char> tempFollow;
                        bool containsEpsilon = true;

                        for (int j = i + 1; j < rule.length(); j++) {
                            char nextSymbol = rule[j];
                            if (isupper(nextSymbol)) {
                                containsEpsilon = false;
                                for (char ch : firstSets[nextSymbol]) {
                                    if (ch != 'ε') tempFollow.insert(ch);
                                }
                                if (firstSets[nextSymbol].count('ε') == 0) break;
                            } else {
                                tempFollow.insert(nextSymbol);
                                containsEpsilon = false;
                                break;
                            }
                        }

                        if (containsEpsilon || tempFollow.count('ε')) {
                            for (char ch : followSets[nonTerminal]) {
                                if (followSets[symbol].insert(ch).second) updated = true;
                            }
                        }
                        for (char ch : tempFollow) {
                            if (followSets[symbol].insert(ch).second) updated = true;
                        }
                    }
                }
            }
        }
    } while (updated);
}

const std::map<char, std::set<char>>& Grammar::getFirstSets() const {
    return firstSets;
}

const std::map<char, std::set<char>>& Grammar::getFollowSets() const {
    return followSets;
}

void Grammar::printFirstSets() const {
    for (const auto &[nonTerminal, firstSet] : firstSets) {
        std::cout << "FIRST( " << nonTerminal << " ) = { ";
        for (auto it = firstSet.begin(); it != firstSet.end(); ++it) {
            std::cout << *it;
            if (next(it) != firstSet.end()) std::cout << " ";
        }
        std::cout << " }\n";
    }
}

void Grammar::printFollowSets() const {
    for (const auto &[nonTerminal, followSet] : followSets) {
        std::cout << "FOLLOW( " << nonTerminal << " ) = { ";
        for (auto it = followSet.begin(); it != followSet.end(); ++it) {
            std::cout << *it;
            if (next(it) != followSet.end()) std::cout << " ";
        }
        std::cout << " }\n";
    }
}
