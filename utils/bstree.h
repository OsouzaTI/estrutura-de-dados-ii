#ifndef BSTREE_H
#define BSTREE_H

#include "tree.h"


template<typename T>
class BSTnode {
public:
    T value;
    BSTnode* left;
    BSTnode* right;
    BSTnode(T v) : value(v), left(nullptr), right(nullptr) {};
};

template<typename T>
class BSTree {
public:

    BSTree(){};
    BSTnode<T>* root = nullptr;
    void        insert          (T v){ root = _insert(root, v); }
    void        remove          (T v){ root = _remove(root, v); }
    void        infoTree2D      (){_print2D(root, 10);}
    void        info            (int order){_info(root, order);}
private:
    BSTnode<T>* _insert         (BSTnode<T>* root, T v);
    BSTnode<T>* _remove         (BSTnode<T>* root, T v);
    int         _depth          (BSTnode<T>* root);
    void        _print2D        (BSTnode<T>* root, int space, int COUNT = 10);
    void        _info           (BSTnode<T>* root, int order, int depth = 0);
};

template<typename T>
void BSTree<T>::_print2D(BSTnode<T>* root, int space, int COUNT){
    if (root == NULL) return;
    space += COUNT;
    _print2D(root->right, space);
    std::cout<<std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
    std::cout << root->value << std::endl;
    _print2D(root->left, space);
}

template<typename T>
void BSTree<T>::_info(BSTnode<T>* root, int order, int depth ){

    if(root == NULL)
        return;

    if(order == PREFIXO){
        std::cout << root->value << " ";
        _info(root->left, order);
        _info(root->right, order);
    }

    if(order == INFIXO){
        _info(root->left, order, depth + 1);
        std::cout << root->value << " ";
        _info(root->right, order, depth + 1);
    }

    if(order == POSFIXO){
        _info(root->left, order);
        _info(root->right, order);
        std::cout << root->value << " ";
    }

}

template<typename T>
int BSTree<T>::_depth(BSTnode<T>* root){
    if(ISNULL(root)) // sub-arvore nula
        return -1;
    int _leftDepth  = _depth(root->left); // 
    int _rightDepth = _depth(root->right);
    return std::max<int>(_leftDepth, _rightDepth) + 1;
}

template<typename T>
BSTnode<T>* BSTree<T>::_insert(BSTnode<T>* root, T value){
    
    if(ISNULL(root))
        return new BSTnode<T>(value);

    if(root->value > value){
        root->left = _insert(root->left, value);
    } else if (root->value < value) {
        root->right = _insert(root->right, value);
    }

    return root;
}

template<typename T>
BSTnode<T>* BSTree<T>::_remove(BSTnode<T>* root, T key){

    {/*
       -- desenhos removidos de: 
            -> https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/

        Existem 3 casos basicos na remoção de um nodo
        da arvore binaria de busca:

        1 - O nodo alvo é uma folha, ou seja, ambos os lados
        esquerdo e direito são nulos.

                    50                              50
                  /     \         delete(20)      /   \
                30      70       --------->    30     70 
                /  \    /  \                     \    /  \ 
              20   40  60   80                   40  60   80

        2 - O nodo alvo possui um filho.
              
              50                            50
           /     \         delete(30)      /   \
          30      70       --------->    40     70 
            \    /  \                          /  \ 
            40  60   80                       60   80

        3 - O nodo alvo possui dois filhos.

              50                            60
           /     \         delete(50)      /   \
          40      70       --------->    40    70 
                 /  \                            \ 
                60   80                           80
        

    */}

    BSTree<T>* aux;

    if(ISNULL(root))
        return nullptr;
    
    // caso 1
    if(ISNULL(root->left) && ISNULL(root->right)){
        if(root->value == key)
            root = nullptr;
        delete root;
        return nullptr;
    }

    if(root->value > key)
        root->left = _remove(root->left, key);
    else if(root->value < key)
        root->right = _remove(root->right, key);
    else {

        if(_depth(root->left) > _depth(root->right)){
            aux = (BSTree<T>*)this->inPredecessor(root->left);
            root->value = aux->value;
            root->left = _remove(root->left, aux->value);
        } else {
            aux = (BSTree<T>*)this->inSuccessor(root->right);
            root->value = aux->value;
            root->right = _remove(root->right, aux->value);
        }

    }

    return root;
}

#endif