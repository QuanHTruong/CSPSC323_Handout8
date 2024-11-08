#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm> // For std::remove_if

using namespace std;

// Utility function to trim whitespace from a string
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

class Grammar {
public:
    map<char, vector<string>> productions; // Stores productions for each non-terminal
    map<char, set<char>> firstSets;        // First sets for each non-terminal
    map<char, set<char>> followSets;       // Follow sets for each non-terminal

    void loadFromFile(const string &filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            line = trim(line); // Trim whitespace around the line
            if (line.empty()) continue;
            
            char nonTerminal = line[0];
            string production = trim(line.substr(3)); // Skip "->" and trim any surrounding whitespace
            productions[nonTerminal].push_back(production);
        }
        file.close();
    }
    //Productions recorded 
    // {'E', {"E+T", "E-T", "T"}},
    // {'T', {"T*F", "T/F", "F"}},
    // {'F', {"(E)", "i"}}

    // function to print out productions gotten from text file 

    // void printProductions() const {
    //     cout << "Productions:\n";
    //     for (const auto &[nonTerminal, rules] : productions) {
    //         cout << nonTerminal << " -> ";
    //         for (size_t i = 0; i < rules.size(); ++i) {
    //             cout << rules[i];
    //             if (i != rules.size() - 1) cout << " | ";
    //         }
    //         cout << "\n";
    //     }
    // }
        
    void computeFirst() {
        bool updated;// boolean flag to keep the loop to find all first set for all non - terminal
        do {
            updated = false; //initialize this as false
            for (auto &[nonTerminal, rules] : productions) { //first loop wheere its loop through each line of CFG
                for (const string &rule : rules) { // second loop for each line of the CFG
                    for (int i = 0; i < rule.length(); i++) { // third loop to go through each symbols, exaple E->E+T; it loops through E,+,T
                        char symbol = rule[i];
                        if (isupper(symbol)) { // Non-terminal 
                            for (char ch : firstSets[symbol]) {
                                if (firstSets[nonTerminal].insert(ch).second) updated = true;
                            }
                            // Check if the first set of the non-terminal contains ε
                            if (firstSets[symbol].count('ε') == 0) break;
                        } else { // Terminal
                            if (firstSets[nonTerminal].insert(symbol).second) updated = true;
                            break;
                        }
                    }
                }
            }
        } while (updated);
    }

    void computeFollow() {
        followSets['E'].insert('$'); // Assuming 'E' is the start symbol
        bool updated;
        do {
            updated = false;
            for (auto &[nonTerminal, rules] : productions) {
                for (const string &rule : rules) {
                    for (int i = 0; i < rule.length(); i++) {
                        char symbol = rule[i];
                        if (isupper(symbol)) { // Only for non-terminals, it is checking if symbol is an uppercase letter
                            set<char> tempFollow;
                            bool allEpsilon = true;

                            for (int j = i + 1; j < rule.length(); j++) {
                                char nextSymbol = rule[j];
                                if (isupper(nextSymbol)) { // Non-terminal
                                    allEpsilon = false;
                                    for (char ch : firstSets[nextSymbol]) {
                                        if (ch != 'ε') tempFollow.insert(ch);
                                    }
                                    // If the first set of nextSymbol doesn't contain ε, break
                                    if (firstSets[nextSymbol].count('ε') == 0) break;
                                } else { // Terminal
                                    tempFollow.insert(nextSymbol);
                                    allEpsilon = false;
                                    break;
                                }
                            }

                            if (allEpsilon || tempFollow.count('ε')) {
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

    //Updated print functions to match the specified format
    void printFirst() const {
        for (const auto &[nonTerminal, firstSet] : firstSets) {
            cout << "FIRST( " << nonTerminal << " ) = { ";
            for (auto it = firstSet.begin(); it != firstSet.end(); ++it) {
                cout << *it;
                if (next(it) != firstSet.end()) cout << " ";
            }
            cout << " }\n";
        }
    }

    void printFollow() const {
        for (const auto &[nonTerminal, followSet] : followSets) {
            cout << "FOLLOW( " << nonTerminal << " ) = { ";
            for (auto it = followSet.begin(); it != followSet.end(); ++it) {
                cout << *it;
                if (next(it) != followSet.end()) cout << " ";
            }
            cout << " }\n";
        }
    }

    void initialize_production(const string &filename){
        loadFromFile(filename); 
        computeFirst();
        computeFollow(); 
        // printFirst();
        // printFollow(); 
    }

};