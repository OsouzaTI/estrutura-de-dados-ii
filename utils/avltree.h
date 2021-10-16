#ifndef AVLTREE_H
#define AVLTREE_H

#include "tree.h"

template<typename T>
class AVLnode {
public:
    int depth;
    T value;
    AVLnode* left;
    AVLnode* right;
    AVLnode(T v) : value(v), left(nullptr), right(nullptr), depth(0) {};
};

template<typename T>
class AVLTree {
private:
    int balance(AVLnode<T>* nodo);
public:
    AVLnode<T>* root = nullptr;
    AVLTree(){};
    inline int  getDepth            (){ return root->depth; };
    void        infoTree2D          (){_print2D(root, 10);}
    void        insert              (T v){ root = _insert(root, v); }
    void        remove              (T v){ root = _remove(root, v); }
    void        info                (int order){_info(root, order);}
private:
    AVLnode<T>* _insert         (AVLnode<T>* root, T v);
    AVLnode<T>* _remove         (AVLnode<T>* root, T v);
    int         _depth          (AVLnode<T>* nodo);
    AVLnode<T>* _rightRotate    (AVLnode<T>* x);
    AVLnode<T>* _leftRotate     (AVLnode<T>* x);  
    void        _print2D        (AVLnode<T>* root, int space, int COUNT = 10);
    void        _info           (AVLnode<T>* root, int order, int depth = 0);
};

template<typename T>
void AVLTree<T>::_print2D(AVLnode<T>* root, int space, int COUNT){
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
void AVLTree<T>::_info(AVLnode<T>* root, int order, int depth){

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
AVLnode<T>* inPredecessor(AVLnode<T>* root){
    while(root && root->right != nullptr)
        root = root->right;
    return root;
};

template<typename T>
AVLnode<T>* inSuccessor(AVLnode<T>* root){
    while(root && root->left != nullptr)
        root = root->left;
    return root;
}; 

template<typename T>
AVLnode<T>* AVLTree<T>::_rightRotate(AVLnode<T>* x){

    AVLnode<T>* y  = x->left;
    AVLnode<T>* t2 = y->right;

    y->right = x;
    x->left = t2;

    x->depth = std::max<int>(_depth(x->left), _depth(x->right)) + 1;
    y->depth = std::max<int>(_depth(y->left), _depth(y->right)) + 1;

    return y;
    
}

template<typename T>
AVLnode<T>* AVLTree<T>::_leftRotate(AVLnode<T>* x){

    AVLnode<T>* y  = x->right;
    AVLnode<T>* t2 = y->left;

    y->left = x;
    x->right = t2;

    x->depth = std::max<int>(_depth(x->left), _depth(x->right)) + 1;
    y->depth = std::max<int>(_depth(y->left), _depth(y->right)) + 1;

    return y;
    
}

template<typename T>
int AVLTree<T>::_depth(AVLnode<T>* nodo){
    if(ISNULL(nodo))
        return -1;
    return nodo->depth;
}

template<typename T>
int AVLTree<T>::balance(AVLnode<T>* nodo){
    if (ISNULL(nodo))
        return 0;
    return _depth(nodo->left) - _depth(nodo->right);
}

template<typename T>
AVLnode<T>* AVLTree<T>::_insert(AVLnode<T>* root, T value){

    if(ISNULL(root))
        return new AVLnode<T>(value);
    
    if(root->value > value)
        root->left  = _insert(root->left, value);
    else if(root->value < value)
        root->right = _insert(root->right, value);
    else 
        return root;

    root->depth = 1 + std::max<int>(
        _depth(root->left),
        _depth(root->right)
    );
    
    int _balance = balance(root);

    if(_balance > 1  && value < root->left->value)
        return _rightRotate(root);

    if(_balance < -1 && value > root->right->value)
        return _leftRotate(root);
    
    // Left Right Case
    if (_balance > 1 && value > root->left->value){
        root->left = _leftRotate(root->left);
        return _rightRotate(root);
    } 

    // Right Left Case
    if (_balance < -1 && value < root->right->value){
        root->right = _rightRotate(root->right);
        return _leftRotate(root);
    }

    return root;
}

template<typename T>
AVLnode<T>* AVLTree<T>::_remove(AVLnode<T>* root, T key){

    if(ISNULL(root))
        return nullptr;

    if (ISNULL(root->left) && ISNULL(root->right)){
        if (root->value == key)
            root = nullptr;
        delete root;
        return nullptr;
    }

    // procurando o nodo a ser removido recursivamente
    if (key < root->value){
        root->left = _remove(root->left, key);
    } else if (key > root->value){
        root->right = _remove(root->right, key);
    } else {
        AVLnode<T>* q = nullptr; // nodo auxiliar

        // caso o lado esquerdo seja mais profundo que o direito
        // escolho o inorder predecessor ( antecessor em ordem )
        if (_depth(root->left) > _depth(root->right)){
            q = inPredecessor(root->left);
            root->value = q->value;
            root->left = _remove(root->left, q->value);
        } 
        // caso contrario, escolho o sucessor em ordem,
        // assim mantendo a arvore bem nivelada
        else {
            q = inSuccessor(root->right);
            root->value = q->value; // troca o valor
            // remove o nodo trocado com alvo da remoção 
            // (recursivamente para refazer todo o balanceamento).
            root->right = _remove(root->right, q->value);
        }
    }

    // atualiza a altura da raiz
    root->depth = 1 + std::max<int>(
        _depth(root->left),
        _depth(root->right)
    );

    // rotações conforme o nodo estiver desalanceado
    int _balance     =  balance(root);
    int leftBalance  =  balance(root->left);
    int rightBalance =  balance(root->right);

    // Balance Factor and Rotation
    if (_balance > 1 && leftBalance >= 0) { 
        // left left rotate
        return _rightRotate(root);
    } else if (_balance > 1 && leftBalance < 0){
        // left right rotate
        root->left = _leftRotate(root->left);
        return _rightRotate(root);
    } else if (_balance < -1 && rightBalance <= 0){
        // right right rotate
        return _leftRotate(root);
    } else if (_balance < -1 && rightBalance > 0){
        // right left rotate
        root->right = _rightRotate(root->right);
        return _leftRotate(root);
    }
    // retorna a raiz
    return root;
};

#endif