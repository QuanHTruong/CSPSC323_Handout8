#include <iostream>
#include "first_follow.cpp"  

void printFirst( map<char, set<char>> firstSets) const {
        for (const auto &[nonTerminal, firstSet] : firstSets) {
            cout << "FIRST( " << nonTerminal << " ) = { ";
            for (auto it = firstSet.begin(); it != firstSet.end(); ++it) {
                cout << *it;
                if (next(it) != firstSet.end()) cout << " ";
            }
            cout << " }\n";
        }
}
int main(){
    Grammar grammar; 
    grammar.initialize_production("CFG.txt");
    printFirst(grammar.firstSets);
    return 0; 
}