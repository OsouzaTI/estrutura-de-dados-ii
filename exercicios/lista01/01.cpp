//============================================
// Soma dos 100 primeiros numeros naturais.
// numeros naturais são compreendidos entre os
// numeros positivos inteiros maiores que zero
// ex: ...1, 2, 3...n
//============================================
#include <iostream>
#include <algorithm>
#include <vector>

const int lim = 25;
int main(){

    std::vector<int> l(lim);
    std::generate(l.begin(), l.end(), [i=1, j=2]()mutable{
        if(j > lim)std::cout << i << std::endl;
        return i += j++;      
    });       

    return 0;
}