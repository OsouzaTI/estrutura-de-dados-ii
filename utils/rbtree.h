#ifndef RB_TREE
#define RB_TREE

#include "tree.h"
#include <map>

enum RBColor {BLACK = 0, RED};
typedef RBColor RBColor;

const std::map<RBColor, std::string> nameColor = {
    {BLACK, "Black"},
    {RED,   "Red"},
};


template<typename T>
class RBTnode {
public:
    T value;
    RBTnode<T>* left;
    RBTnode<T>* right;
    RBTnode<T>*  parent;
    RBColor  color;
    RBTnode(){};
    RBTnode(T v) 
        :   value(v),
            left(nullptr),
            right(nullptr),
            color(BLACK) {};
};

template<typename T>
class RBTree {
public:
    RBTree(){
        nil = new RBTnode<T>();
        nil->color = BLACK;
        nil->left  = nullptr;
        nil->right = nullptr;
        root = nil;
    };
    RBTnode<T>* root;
    RBTnode<T>* nil;
    void        infoTree2D      (){_print2D(root, 10);}
    void        insert          (T v){ _insert(v); }
    void        remove          (T v){ _remove(root, v); }

    void        infoTree        (int order = INFIXO);

private:    
    void        _insert         (T _z);
    void        _remove         (RBTnode<T>* z, T key);
    bool        _isNil          (RBTnode<T>* n);
    RBTnode<T>* _minimum        (RBTnode<T>* root);
    void        _insert_fixup   (RBTnode<T>* z);
    void        _remove_fixup   (RBTnode<T>* n);
    void        _transplant     (RBTnode<T>* u, RBTnode<T>* v);
    void        _left_rotate    (RBTnode<T>* x);
    void        _right_rotate   (RBTnode<T>* y);
    void        _print2D        (RBTnode<T>* root, int space, int COUNT = 10);
    void        _prefixo        (RBTnode<T>* root);
    void        _infixo         (RBTnode<T>* root);
    void        _posfixo        (RBTnode<T>* root);
};

template<typename T>
void RBTree<T>::_print2D(RBTnode<T>* root, int space, int COUNT){
    if (root == nil || root == nullptr) return;
    space += COUNT;
    _print2D(root->right, space);
    std::cout<<std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
    std::cout << root->value << "["
        << nameColor.at(root->color) <<
    "]"<< std::endl;
    _print2D(root->left, space);
}


template<typename T>
void RBTree<T>::infoTree (int order) {
	switch (order)
    {
        case PREFIXO:{
            std::cout << "PREFIXO: ";
            _prefixo(root);
        }break;
        case INFIXO :{
            std::cout << "INFIXO: ";
            _infixo(root);
        }break;
        case POSFIXO:{
            std::cout << "POSFIXO: ";
            _posfixo(root);    
        }break;
        default:break;
    }
    std::cout << std::endl;
}

template<typename T>
void RBTree<T>::_prefixo(RBTnode<T>* root){
	if(root != nil){
		printf("%d\t", root->value);
		_prefixo(root->left);
		_prefixo(root->right);
	}
}

template<typename T>
void RBTree<T>::_infixo(RBTnode<T>* root){
	if(root != nil){
		_infixo(root->left);
		printf("%d\t", root->value);
		_infixo(root->right);
	}
}

template<typename T>
void RBTree<T>::_posfixo(RBTnode<T>* root){
	if(root != nil){
		_posfixo(root->left);
		_posfixo(root->right);
		printf("%d\t", root->value);
	}
}

template<typename T>
void RBTree<T>::_insert(T _z){
    printf("Usando o insert do Red Black Tree\n");
    RBTnode<T>* z = new RBTnode<T>();
    z->color  = RED; // novo nodo deve ser vermelho
    z->parent = nullptr;
    z->left   = nil;
    z->right  = nil;
    z->value  = _z;

    RBTnode<T>* y = nil;
    RBTnode<T>* x = root;

    while(x != nil){
        y = x;
        if(z->value < x->value)
            x = x->left;
        else
            x = x->right;
    }

    if(y == nil)
        root = z;
    else if(z->value <= y->value)
        y->left = z;
    else
        y->right = z;

    z->parent = y;
    _insert_fixup(z);

}

template<typename T>
RBTnode<T>* RBTree<T>::_minimum(RBTnode<T>* root) {
    while (root->left != nil)
        root = root->left;
    return root;
}


template<typename T>
void RBTree<T>::_remove_fixup(RBTnode<T>* n){
    RBTnode<T> *w;

    while(n != root && n->color == BLACK){

        if(n == n->parent->left){
            
            w = n->parent->right;

            if(w->color == RED){
                w->color = BLACK;
                n->parent->color = RED;
                _left_rotate(n->parent);
                w = n->parent->right;
            }

            if(w->left->color == BLACK && w->right->color == BLACK){

                w->color = RED;
                n->parent->color = BLACK;
                n = n->parent;

            } else {

                if(w->right->color == BLACK){
                    w->color = RED;
                    w->left->color = BLACK;
                    _right_rotate(w);
                    w = n->parent->right;
                }
                w->color = n->parent->color;
                n->parent->color = BLACK;
                n->right->color  = BLACK;
                _left_rotate(n->parent);
                n = root;

            }

        } else {

            w = n->parent->left;

            if(w->color == RED){
                w->color = BLACK;
                n->parent->color = BLACK;
                _right_rotate(n->parent);
                w = n->parent->left;
            }

            if(w->left->color == BLACK && w->right->color == BLACK){

                w->color = RED;
                n->parent->color = BLACK;
                n = n->parent;

            } else {

                if(w->left->color == BLACK){
                    w->color = RED;
                    w->right->color = BLACK;
                    _left_rotate(w);
                    w = n->parent->left;
                }
                w->color = n->parent->color;
                n->parent->color = BLACK;
                w->left->color   = BLACK;
                _right_rotate(n->parent);
                n = root;

            }
        }
    } 
    n->color = BLACK;
}

template<typename T>
void RBTree<T>::_remove(RBTnode<T>* n, T key){
        
    RBTnode<T> *y, *x, *z;
    
    // procurando o nodo
    while (n != nil) {

        if(n->value == key) {
            z = n;
            break;            
        } 
        
        if(n->value > key) {
            n = n->left;
        } else {
            n = n->right;
        }
    }

    std::cout << z->value << std::endl;

    y = z;
    RBColor y_ori = y->color;
    if(z->left == nil){
        x = z->right;
        _transplant(z, z->right);
    } else if (z->right == nil){
        x = z->left;
        _transplant(z, z->left);
    } else {
        y = _minimum(z->right);
        y_ori = y->color;
        x = y->right;
        if(y->parent == z) {
            x->parent = y;
        } else {
            _transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        _transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(y_ori == BLACK)
        _remove_fixup(x);
}

template<typename T>
void RBTree<T>::_insert_fixup(RBTnode<T>* z){

    while(z->parent->color == RED){
        
        if(z->parent == z->parent->parent->left) {

            if(z->parent->parent->right->color == RED){
                z->parent->color = BLACK;
                z->parent->parent->right->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {

                if(z == z->parent->right){
                    z = z->parent;
                    _left_rotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                _right_rotate(z->parent->parent);

            }

        } else {

            if(z->parent->parent->left->color == RED){

                z->parent->color = BLACK;
                z->parent->parent->left->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;

            } else {

                if(z == z->parent->left){
                    z = z->parent;
                    _right_rotate(z);
                }                
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                _left_rotate(z->parent->parent);

            }

        }

    }
    root->color = BLACK;
}

template<typename T>
void RBTree<T>::_transplant(RBTnode<T>* u, RBTnode<T>* v){
    if(ISNULL(u->parent))
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else 
        u->parent->right = v;
    v->parent = u->parent;
}

template<typename T>
void RBTree<T>::_left_rotate(RBTnode<T>* x){
    RBTnode<T>* y = x->right;
    x->right = y->left;
    if(y->left != nil)
        y->left->parent = x;
    y->parent = x->parent;
    if(y->parent == nil)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else 
        x->parent->right = y;
    y->left   = x;
    x->parent = y;
}

template<typename T>
void RBTree<T>::_right_rotate(RBTnode<T>* x){
    RBTnode<T>* y = x->left;
    x->left = y->right;
    if(y->right != nil)
        y->right->parent = x;
    y->parent = x->parent;
    if(y->parent == nil)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else 
        x->parent->right = y;
    y->right  = x;
    x->parent = y; 
}

#endif