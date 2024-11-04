#include <iostream>
#include "first_follow.cpp"  

int main(){
    Grammar grammar; 
    grammar.initialize_production("CFG.txt");
    System.out.print(grammar.firstSets)
    return 0; 
}