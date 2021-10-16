#include <iostream>
#include "bstree.h"
#include "avltree.h"
#include "rbtree.h"

namespace Test {
    
    void remove(){
        
        // AVLTree<int> t;
        // t.insert(10);
        // t.insert(20);
        // t.insert(30);
        // t.insert(40);
        // t.insert(50);
        // t.insert(25);
        // t.infoTree2D();
        // std::cout << "--------------------------" << std::endl;
        // t.remove(40);
        // t.infoTree2D();
        // std::cout << "--------------------------" << std::endl;
        // t.remove(25);
        // t.infoTree2D();
        // std::cout << "--------------------------" << std::endl;
        // t.remove(30);
        // t.infoTree2D();
        // t.info(PREFIXO);

        RBTree<int> rb;
        rb.insert(1);
        rb.insert(4);
        rb.insert(3);
        rb.insert(45);
        rb.insert(23);
        rb.insert(24);

        rb.infoTree2D();
        rb.remove(23);
        std::cout << "-------------------------------\n";
        rb.infoTree2D();

        rb.infoTree(INFIXO);
        rb.infoTree(PREFIXO);
        rb.infoTree(POSFIXO);

    }

    void insertSingle(){
        
        std::cout << std::string(
        "*----------------------------------------------- \n"
        "| AVL insert single values                       \n"
        "-----------------------------------------------  \n");

        AVLTree<int> t;
        t.insert(10);
        t.insert(20);
        t.insert(30);
        t.insert(40);
        t.insert(50);
        t.insert(25);
        t.infoTree2D();
        t.info(PREFIXO);

        std::cout << std::string(
        "\n*----------------------------------------------- "
        "\n| BST insert single values                       "
        "\n----------------------------------------------- \n");

        BSTree<int> b;

        b.insert(10);
        b.insert(20);
        b.insert(30);
        b.insert(40);
        b.insert(50);
        b.insert(25);
        b.infoTree2D();
        b.info(PREFIXO);

    }

    void rbtInsert(){
        RBTree<int> rb;
        rb.insert(10);
        rb.insert(12);
        rb.insert(13);
        rb.infoTree2D();
    }

}

int main(){
    
    Test::remove();

    return 0;
}