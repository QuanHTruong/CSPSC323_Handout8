#include <iostream>
#include "first_follow.cpp" 
#include "closure_goto.cpp"
#include "parsingtable.cpp" 

int main(){
    Grammar grammar; 
    grammar.initialize_production("CFG.txt");
    
    return 0; 
}