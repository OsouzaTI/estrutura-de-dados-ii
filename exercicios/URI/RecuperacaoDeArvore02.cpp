#include <iostream>
#include <map>
#include <vector>
#include "../../utils/tree.h"
#include <algorithm>

std::map<char, int> priority = { // CBAD
    {'C', 0},
    {'B', 1},
    {'A', 2},
    {'D', 3}
};

bool comparator(char a, char b, int selector){

    switch (selector)
    {
        case 0: return priority[a] > priority[b]; 
        case 1: return priority[a] < priority[b];   
        default:{ return false; };
    }

}

int main(){

    Rtree<char> r{comparator};
    r.insertCmp(std::vector<char>{'B', 'C', 'A', 'D'});
    std::cout << "\n";
    r.info(r.root, POSFIXO);    
    // t.print2D(t.root, 10);

    return 0;
}