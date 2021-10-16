#include <iostream>
#include <map>
#include "../../utils/tree.h"
#include <algorithm>

std::map<char, int> map;

bool comparator(char a, char b, uchar_t selector){
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

    Rtree<char> r{comparator};
    std::string prefixo, infixo;    
    while (true)
    {   

        if(!(std::cin >> prefixo)||!(std::cin >> infixo))
            break;

        // criando as prioridades de inserção
        for(int i = 0; i < infixo.size(); i++)
            map[infixo[i]] = i;

        // adicionando em ordem prefixa
        std::for_each(prefixo.begin(), prefixo.end(), [&r](char c){
            r.insertCmp(c);
        });

        r.info(r.root, POSFIXO);
        std::cout << "\n";

        // r.clearTree();         
        map.clear();  
    }
    return 0;
}