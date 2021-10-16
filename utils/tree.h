#ifndef TREE_HPP
#define TREE_HPP
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <assert.h>

#define ISNULL(x) (x == nullptr)
#define COMPARE(x, y) (x == y)
#define _LOGGER_ true

namespace Helpers {

    class LOGGER {
    public:
        static void LOG(std::string x){
    #if _LOGGER_
            std::cout << x << std::endl;
    #endif
        }
        static void LOG(std::string x, int y){
    #if _LOGGER_
            // std::cout <<"["<<x<<"]"<<"["<<y<<"]"<<std::endl;
            std::cout << y << " ";
    #endif
        }
    };

    std::string reverse(std::string str){
        std::string reversed;
        int size = str.size();
        for(int i = size; i > 0; i--)
            reversed.push_back(str.at(i - 1));
        return reversed;
    }

    namespace ExpTree {

        int precedence(char k){
            std::map<char, int> _map = {
                {'^', 3},
                {'/', 2},
                {'*', 2},
                {'+', 1},
                {'-', 1},
            };
            if(_map.count(k) == 0)
                return -1;
            return _map[k];
        }

        bool isOperator(char op){
            return op == '+' || op == '-' || op == '*' || op == '/';
        };

        bool isOperand(char op){
            return (op >= 'a' && op <= 'z') ||
                (op >= 'A' && op <= 'Z') ||
                (op >= '0' && op <= '9');
        }

        /// algoritmo baseado na versão do :
        /// https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
        std::string expressionInfixToPosfix(std::string& infix){
            
            std::string      expression;
            std::stack<char> operations;

            // remove espaços em branco da string
            infix.erase(std::remove_if(infix.begin(), infix.end(), isspace), infix.end());

            for(char k : infix){   

                if(isOperand(k))
                    expression.push_back(k);            
                else if(k == '(') operations.push(k);
                else if(k == ')') {
                    while(operations.top() != '('){
                        expression.push_back(operations.top());
                        operations.pop();
                    }
                    operations.pop();
                } else {
                    while(!operations.empty() && precedence(k) <= precedence(operations.top())){
                    expression.push_back(operations.top());
                    operations.pop();
                    }
                    operations.push(k);
                }
            }

            while(!operations.empty()){
                expression.push_back(operations.top());
                operations.pop();
            }

            return expression;
        }

    }

}


enum PERCURSE  {
    PREFIXO, // percurso [Raiz     | Esquerda | Direita]
    INFIXO,  // percurso [Esquerda | Raiz     | Direita]
    POSFIXO  // percurso [Esquerda | Direita  | Raiz   ]
};
enum TREE_TYPE { 
    BST,     // Binary Search Tree
    AVL,     // Balanced Binary Search Tree
    RBT,
    NONE     // No type selected
};

typedef unsigned char uchar_t;
typedef TREE_TYPE treetype_t;

#endif
