// Grammar.h

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <string>
#include <map>
#include <set>
#include <vector>

class Grammar {
public:
    Grammar();  // Constructor
    void initializeProduction(const std::string &filename);
    void computeFirstSets();
    void computeFollowSets();
    const std::map<char, std::set<char>>& getFirstSets() const;
    const std::map<char, std::set<char>>& getFollowSets() const;
    void printFirstSets() const;
    void printFollowSets() const;

private:
    std::map<char, std::vector<std::string>> productions; // Productions for each non-terminal
    std::map<char, std::set<char>> firstSets;             // First sets for each non-terminal
    std::map<char, std::set<char>> followSets;            // Follow sets for each non-terminal

    std::string trim(const std::string &str);
};

#endif // GRAMMAR_H
