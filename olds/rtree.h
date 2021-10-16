// #ifndef RTREE_H
// #define RTREE_H

// #include "tree.h"
// #include "bstree.h"
// #include "avltree.h"
// #include "rbtree.h"

// template<typename T, class G>
// class Rtree : public G {  
// private:
//     G*          root = nullptr;
//     void        print2D       (G* root, int space, int COUNT = 10);
//     G*          find          (G* root, T v);
//     Tree<T>*    inPredecessor (Tree<T>* root) override;
//     Tree<T>*    inSuccessor   (Tree<T>* root) override;
//     T           min           (G* root);
//     T           max           (G* root);
//     void        info          (G* root, int order, int depth = 0);
// public:
//     Rtree(){};
//     void insert (T value);
//     void remove (T value);
//     void depth  (T value);
//     void info   (int order);
//     inline void infoTree2D(){print2D(this->root, 10);}
// };

// template<typename T, class G>
// void Rtree<T, G>::insert(T value){
//     if(this->tType == AVL || this->tType == BST)
//         this->root = this->_insert(this->root,value);
//     else
//         this->_insert(this->root,value);
// }

// template<typename T, class G>
// void Rtree<T, G>::remove(T value){
//     // G* nodo = find(this->root, value);
//     // if(nodo == NULL)return;
//     // std::cout << "find[" << nodo->value << "]" << std::endl;
//     // achou o nodo na arvore
//     this->_remove(this->root, value);
// }

// template<typename T, class G>
// void Rtree<T, G>::print2D(G* root, int space, int COUNT){
//     if (root == NULL) return;
//     space += COUNT;
//     print2D(root->right, space);
//     std::cout<<std::endl;
//     for (int i = COUNT; i < space; i++)
//         std::cout<<" ";
//     root->infoValue();
//     print2D(root->left, space);
// }

// template<typename T, class G>
// G* Rtree<T, G>::find(G* root, T key){
//     if(root == NULL)
//         return NULL;
//     if(root->value == key)        
//         return root;    
//     if(root->value > key)
//         return find(root->left, key);
//     return find(root->right, key);
// }

// template<typename T, class G>
// Tree<T>* Rtree<T, G>::inPredecessor(Tree<T>* root){
//     while(root&&root->right != NULL)root = root->right;
//     return root;
// }

// template<typename T, class G>
// Tree<T>* Rtree<T, G>::inSuccessor(Tree<T>* root){
//     while(root&&root->left != NULL)root = root->left;
//     return root;
// }

// template<typename T, class G>
// T Rtree<T, G>::min(G* root){
//     G* n;
//     for(n = root;n->left;n = n->left);
//     return n->value;
// }

// template<typename T, class G>
// T Rtree<T, G>::max(G* root){
//     G* n;
//     for(n = root;n->right;n = n->right);
//     return n->value;
// }


// template<typename T, class G>
// void Rtree<T, G>::info(int order){
//     info(this->root, order);
// }

// template<typename T, class G>
// void Rtree<T, G>::info(G* root, int order, int depth){

//     if(root == NULL)
//         return;

//     if(order == PREFIXO){
//         std::cout << root->value << " ";
//         info(root->left, order);
//         info(root->right, order);
//     }

//     if(order == INFIXO){
//         info(root->left, order, depth + 1);
//         std::cout << root->value << " ";
//         info(root->right, order, depth + 1);
//     }

//     if(order == POSFIXO){
//         info(root->left, order);
//         info(root->right, order);
//         std::cout << root->value << " ";
//     }

// }

// #endif