#include <iostream>
#include "first_follow.cpp"  

int main(){
    Grammar grammar; 
    grammar.initialize_production("CFG.txt");
    printf((string)grammar.firstSets)
    return 0; 
}