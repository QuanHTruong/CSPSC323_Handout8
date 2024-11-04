#include <iostream>
#include "first_follow.cpp"  

int main(){
    Grammar grammar; 
    grammar.initialize_production("CFG.txt");
    printf(grammar.firstSets)
    return 0; 
}