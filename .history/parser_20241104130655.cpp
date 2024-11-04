#include <iostream>
#include "Grammar.cpp"  

int main(){
    Grammar grammar; 
    grammar.intialize_production("CFG.txt");
    return 0; 
}