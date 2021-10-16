#include <iostream>
#include "../../utils/tree.h"

std::map<int, int> map;

bool comparator(int a, int b, uchar_t selector){
    switch (selector)
    {
        case 0:{// IF - se true, adiciona na esquerda
            return map[a] > map[b]; 
        }break;
        case 1:{// ELSE IF - se true, adiciona na direita
            return map[a] < map[b];
        };   
        default:{ return false; };
    }
}

int main(){
    
    {/*

        3.1) 
        Pré: 1 6 7 8
        In: 1 6 8 7
        Pós:

    */}

    Rtree<int> r{comparator};  
    std::vector<int> prefixo{40, 25, 20, 10, 15, 23, 32, 28, 82, 55, 90, 87, 100};
    std::vector<int> infixo{10, 15, 20, 23, 25, 28, 32, 40, 55, 82, 87, 90, 100};

    // criando as prioridades de inserção
    for(int i = 0; i < infixo.size(); i++)
        map[infixo[i]] = i;

    // adicionando em ordem prefixa
    std::for_each(prefixo.begin(), prefixo.end(), [&r](char c){
        r.insertCmp(c);
    });

    r.info(r.root, POSFIXO, 0);
    std::cout << "\n";

    r.clearTree();         
    map.clear();


    return 0;
}