#include <iostream>
#include <vector>
#include <algorithm>
#include "../../utils/tree.h"

#define MAX_C 1000

int main(){
    Rtree<int> r;
    std::vector<int> numbers;
    int c;

    std::cin >> c; // numeros de entradas
    for(int i = 0; i < c; i++){
        int n, k;
        std::cin >> n; // numeros de elementos
        for(int j = 0; j < n; j++){
            std::cin >> k; // adicionando elementos no vetor
            numbers.push_back(k);
        }
        // adicionando elementos na arvore
        std::for_each(numbers.begin(), numbers.end(), [&r](int p){
            r.insert(p);    
        });
        
        std::cout << "Case " << (i+1) << ":" << std::endl;
        std::cout << "Pre.:";
        r.info(r.root, PREFIXO);
        std::cout << std::endl;

        std::cout << "In..:";
        r.info(r.root, INFIXO);
        std::cout << std::endl;

        std::cout << "Post:";
        r.info(r.root, POSFIXO);
        std::cout << std::endl;
        
        std::cout << std::endl;

        numbers.clear();
        r.clearTree();
    }

    return 0;
}