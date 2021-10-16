#include <iostream>
#include <map>
#include "../../utils/tree.h"

// Operações
enum {
    INSERT,
    LIST_INF,
    LIST_PRE,
    LIST_POS,
    SEARCH
};

// parse
std::map<std::string, int> table = {
    {"I"      , INSERT  },
    {"INFIXA" , LIST_INF},
    {"PREFIXA", LIST_PRE},
    {"POSFIXA", LIST_POS},
    {"P"      , SEARCH  },
};

void info(Rtree<char>& r){
    int stackSize = r.getPercurse()->size();
    for(int i = 0; i < stackSize; i++){
        std::cout << r.getPercurse()->front();
        if(i < stackSize - 1)
            std::cout << " ";  
        r.getPercurse()->pop();      
    }
}

int main(){

    Rtree<char> r;
    std::string op;
    char k;
    while(true){

        if(!(std::cin >> op)){
            break;
        }else{
            if(op.compare("I") == 0 || op.compare("P") == 0)
                std::cin >> k;
        }
            
        
        switch (table[op])
        {
            case INSERT:{
                r.insert(k);
            }break;
            case LIST_INF:{
                r.info(r.root, INFIXO);
                info(r);
                std::cout << "\n";
            }break;
            case LIST_PRE:{
                r.info(r.root, PREFIXO);
                info(r);
                std::cout << "\n";
            }break;
            case LIST_POS:{
                r.info(r.root, POSFIXO);
                info(r);
                std::cout << "\n";
            }break;
            case SEARCH:{
                if(r.exists(r.root, k)){
                    std::cout << k << " existe" << std::endl;
                }else{
                    std::cout << k << " nao existe" << std::endl;
                }                
            }break;
            default: break;
            
        }
        

    }


    return 0;
}