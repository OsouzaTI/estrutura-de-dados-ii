#include <iostream>
#include "../../utils/tree.h"

int main(){

    Rtree<int> t;
    t.insert(12);
    t.insert(16);
    t.insert(18);
    t.insert(10);
    t.insert(14);
    t.insert(20);
    std::cout << t.min(t.root) << std::endl;
    std::cout << t.max(t.root) << std::endl;
    std::cout << t.depth(t.root) << std::endl;
    std::cout << t.find(t.root, 12)->value << std::endl;
    t.print2D(t.root, 10);

    return 0;
}