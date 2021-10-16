#include <iostream>
#include <vector>
#include "../../utils/tree.h"


int main(){
    
    Rtree<int> a, b, c, d, e;
    std::cout << "a)" << std::endl;
    a.insert(std::vector<int>{30, 15, 40, 10, 20, 60, 80});
    a.print2D(a.root, 10);
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "b)" << std::endl;
    b.insert(std::vector<int>{30, 15, 40, 10, 20, 80, 60});
    b.print2D(b.root, 10);
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "c)" << std::endl;
    c.insert(std::vector<int>{30, 15, 60, 10, 20, 40, 80});
    c.print2D(c.root, 10);
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "d)" << std::endl;
    d.insert(std::vector<int>{30, 60, 20, 80, 15, 10, 40});
    d.print2D(d.root, 10);
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "e)" << std::endl;
    e.insert(std::vector<int>{30, 60, 40, 10, 20, 15, 80});
    e.print2D(e.root, 10);


    return 0;

}