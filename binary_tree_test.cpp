#include <iostream>

template<typename T>
class Tree {
private:
    inline static Tree<T>* root = NULL;
    Tree<T>* insert(Tree<T>* root, T value){
        if(root == NULL)
            return newNode(value);
        if(root->value > value)
            root->left =  insert(root->left, value);
        else if(root->value < value)
            root->right = insert(root->right, value);
        return root;
    }
    void info(Tree<T>* root){
        if(root == NULL) return;
        info(root->left);
        std::cout << root->value << " ";
        info(root->right);
    }
public:
    T value;
    Tree<T>* left;
    Tree<T>* right;
    void insert(T value){
        if(Tree<T>::root == NULL)
            Tree<T>::root = this->insert(Tree<T>::root, value);
        else
            this->insert(Tree<T>::root, value);
    }
    void info(){ 
        this->info(Tree<T>::root);
    }
    Tree<T>* newNode(T value){
        Tree<T>* n = new Tree<T>();
        n->left = n->right = NULL;
        n->value = value;
        return n;
    }
};

int main(){
    Tree<int> t;
    t.insert(10);
    t.insert(13);
    t.insert(3);
    t.insert(90);
    t.insert(120);
    t.info();
    return 0;
}