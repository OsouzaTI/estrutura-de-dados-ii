#include <iostream>
#include <stack>
#include <vector>
#include "../../utils/tree.h"


int main(){
    
    // std::cout << Helpers::expressionInfixToPosfix("4 * a - ( 6 + b ) + 8 / ( 9 - 7 )") << std::endl;

    std::string expression;
    std::stack<Tree<char>*> tree;
    Tree<char>* node, *helpers[2];
    bool isFirst = true;
    while(std::getline(std::cin, expression) && !std::cin.eof()){
        
        if(!isFirst)
            std::cout << std::endl;

        // convertendo de infixo para posfixo
        expression = Helpers::ExpTree::expressionInfixToPosfix(expression);
        if(expression == "\0" || expression == " ")
            break;

        for(char k : expression){

            if(!Helpers::ExpTree::isOperator(k)){

                node = Tree<char>::emptyNode(k);
                tree.push(node);

            }else{

                node = Tree<char>::emptyNode(k);
                helpers[0] = tree.top();
                tree.pop();
                helpers[1] = tree.top();
                tree.pop();

                node->left  = helpers[0];
                node->right = helpers[1];

                tree.push(node); 

            }

        }

        node = tree.top();
        Rtree<char> t;
        t.setRoot(node);
        t.info(t.root, INFIXO, 0);
        for(int i = 0; i < t.getStringDepth()->size(); i++){
            std::cout << "Nivel " << i << ": " 
                << Helpers::reverse(t.getStringDepth()->at(i));
            if(i < t.getStringDepth()->size() - 1)
                std::cout << std::endl;
        }

        std::cout << std::endl;
        isFirst = false;
    }    
    return 0;
}