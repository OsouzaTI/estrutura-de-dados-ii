#include <iostream>

using namespace std;

template<typename T>
class BTNode {

    T* keys;
    int  t;
    BTNode** ptrChild;
    int n;
    bool leaf;

public:
    BTNode(int t, bool leaf);
    void    traverse            ();
    BTNode* search              (T k);

    void    insertNonFull       (T k);
    void    splitChild          (int i, BTNode<T> *y);
    int     findKey             (int k);
    
    // funcoes helpers de remocao
    void    remove              (T k);

    void    removeFromLeaf      (int idx);
    void    removeFromNonLeaf   (int idx);
    int     getPred             (int idx);
    int     getSucc             (int idx);
    void    fill                (int idx);
    void    borrowFromPrev      (int idx);
    void    borrowFromNext      (int idx);
    void    merge               (int idx);

    template<typename U> friend class Btree;

};

template<typename T>
class Btree
{
    private:
        BTNode<T>* root;
        int t;
    public:
        Btree(int t);
        ~Btree();

        void traverse();
        BTNode<T>* search(T k);
        void insert(T k);
        void remove(T k);
};

template<typename T>
BTNode<T>::BTNode(int t, bool leaf){
    this->t = t;
    this->leaf = leaf;
    this->keys = new T[2 * t - 1];
    this->ptrChild = new BTNode *[2*t];
    this->n = 0;
}

template<typename T>
int BTNode<T>::findKey(int k){

    int idx = 0;
    while(idx < n && keys[idx] < k)
        ++idx;
    return idx;

}

template<typename T>
void BTNode<T>::remove(T k){

    int idx = findKey(k);
    if(idx < n && keys[idx] == k)
    {
        if(this->leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {

        if(this->leaf)
        {
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }

        bool flag = ( (idx==n)? true : false );

        if(ptrChild[idx]->n < t)
            fill(idx);
        
        if(flag && idx > n)
            ptrChild[idx - 1]->remove(k);
        else
            ptrChild[idx]->remove(k);
        
        
    }
    return;
}

template<typename T>
void BTNode<T>::removeFromLeaf(int idx){

    for(int i = idx+1; i < n; ++i)
        keys[i-1] = keys[i];    
    n--;
    return;

}

template<typename T>
void BTNode<T>::removeFromNonLeaf(int idx){
    
    int k = keys[idx];    

    if(ptrChild[idx]->n >= t){
        int pred = getPred(idx);
        keys[idx] = pred;
        ptrChild[idx]->remove(pred);
    } else if(ptrChild[idx+1]->n >= t) {

        int succ = getSucc(idx);
        keys[idx] = succ;
        ptrChild[idx+1]->remove(succ);

    } else {
        merge(idx);
        ptrChild[idx]->remove(k);
    }

    return;
}

template<typename T>
int BTNode<T>::getPred(int idx){
    BTNode* cur = ptrChild[idx];
    while(!cur->leaf)
        cur = cur->ptrChild[cur->n];
    return cur->keys[cur->n - 1];
}

template<typename T>
int BTNode<T>::getSucc(int idx){
    BTNode* cur = ptrChild[idx+1];
    while(!cur->leaf)
        cur = cur->ptrChild[0];
    return cur->keys[0];
}

template<typename T>
void BTNode<T>::fill(int idx){

    if(idx != 0 && ptrChild[idx-1]->n >= t)
        borrowFromPrev(idx);
    else if (idx != n && ptrChild[idx+1]->n >= t)
        borrowFromNext(idx);
    
    else
    {
        if(idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

template<typename T>
void BTNode<T>::borrowFromPrev(int idx){

    BTNode* child   = ptrChild[idx];
    BTNode* sibling = ptrChild[idx - 1];

    for(int i = child->n - 1; i >= 0; --i)
        child->keys[i+1] = child->keys[i];

    if(!child->leaf){
        for(int i = child->n; i >= 0; --i)
            child->ptrChild[i+1] = child->ptrChild[i];
    } 

    child->keys[0] = keys[idx-1];

    if(!child->leaf)
        child->ptrChild[0] = sibling->ptrChild[sibling->n];
    
    keys[idx-1] = sibling->keys[sibling->n-1];

    child->n += 1;
    sibling->n -= 1;

    return;

}

template<typename T>
void BTNode<T>::borrowFromNext(int idx){

    BTNode* child   = ptrChild[idx];
    BTNode* sibling = ptrChild[idx+1];

    child->keys[child->n] = keys[idx];

    if(!child->leaf)
        child->ptrChild[child->n+1] = sibling->ptrChild[0];
    
    keys[idx] = sibling->keys[0];

    for(int i = 1; i < sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];

    if(!sibling->leaf){
        for(int i = 1; i <= sibling->n; ++i)
            sibling->ptrChild[i-1] = sibling->ptrChild[i];
    }

    child->n += 1;
    sibling->n -= 1;

    return;

}

template<typename T>
void BTNode<T>::merge(int idx){

    BTNode* child = ptrChild[idx];
    BTNode* sibling = ptrChild[idx+1];

    child->keys[t-1] = keys[idx];

    for(int i = 0; i < sibling->n; ++i)
        child->keys[i+t] = sibling->keys[i];
    
    if(!child->leaf){
        for(int i = 0; i <= sibling->n; ++i)
            child->ptrChild[i+t] = sibling->ptrChild[i];
    }

    for(int i = idx+1; i < n; ++i)
        keys[i-1] = keys[i];
    
    for(int i = idx+2; i<=n; ++i)
        ptrChild[i-1] = ptrChild[i];
    
    child->n += sibling->n+1;
    n--;

    delete(sibling);
    return;

}

template<typename T>
void BTNode<T>::insertNonFull(T k){

    int i = n - 1;
    
    if(this->leaf){
        while(i >= 0 && this->keys[i] > k){
            this->keys[i + 1] = keys[i];
            i--;
        }

        this->keys[i+1] = k;
        n = n + 1;

    } else {

        while(i >= 0 && keys[i] > k)
            i--;
        
        if(ptrChild[i+1]->n == 2*t-1){
            splitChild(i+1, ptrChild[i+1]);
            if(keys[i+1] < k)
                i++;
        }

        ptrChild[i+1]->insertNonFull(k);

    }

}

template<typename T>
void BTNode<T>::splitChild(int i, BTNode<T> *y){

    BTNode<T>* z = new BTNode(y->t, y->leaf);
    z->n = t - 1;

    int j;
    for(j = 0; j < t -1; j++)
        z->keys[j] = y->keys[j + t];
    
    if(!y->leaf){

        for(int j = 0; j < t; j++)
            z->ptrChild[j] = y->ptrChild[j + t];

    }

    y->n = t - 1;

    for(int j = n; j >= i + 1; j--)
        ptrChild[j+1] = ptrChild[j];
    
    ptrChild[i+1] = z;

    for(int j = n - 1; j >= i; j--)
        keys[j+1] = keys[j];
    
    keys[i] = y->keys[t-1];

    n = n + 1;

}

template<typename T>
void BTNode<T>::traverse()
{   
    int i;
    for (i = 0; i < n; i++)
    {       
        if (leaf == false)
            ptrChild[i]->traverse();
        cout << " " << keys[i];
    }

    
    if (leaf == false)
        ptrChild[i]->traverse();
}

template<typename T>
BTNode<T>* BTNode<T>::search(T k){
    int i = 0;
    while(i < n && k > this->keys[i])
        i++;
    
    if(this->keys[i] == k)
        return this;
    
    if(this->leaf)
        return nullptr;
    
    return ptrChild[i]->search(k);
}


template<typename T>
Btree<T>::Btree(int t)
{
    this->root = nullptr;
    this->t = t;
}

template<typename T>
Btree<T>::~Btree()
{}

template<typename T>
void Btree<T>::traverse(){
    if(this->root != nullptr)
        root->traverse();
}

template<typename T>
BTNode<T>* Btree<T>::search(T k){
    if(this->root == nullptr)
        return nullptr;
    return root->search(k);
}

template<typename T>
void Btree<T>::insert(T k){
    
    if(this->root == nullptr){
        this->root = new BTNode<T>(t, true);
        this->root->keys[0] = k;
        this->root->n = 1;
    }else{

        if(this->root->n == 2*t-1){
            
            BTNode<T>* s = new BTNode<T>(t, false);
            s->ptrChild[0] = this->root;
            s->splitChild(0, this->root);

            int i = 0;
            if(s->keys[0] < k)
                i++;
            
            s->ptrChild[i]->insertNonFull(k);
            this->root = s;


        } else { root->insertNonFull(k); }

    }

}

template<typename T>
void Btree<T>::remove(T k){

    if(!root){
        cout << "The tree is empty\n";
        return;
    }

    root->remove(k);

    if(root->n == 0){
        BTNode<T>* tmp = root;
        if(root->leaf)
            root = nullptr;
        else
            root = root->ptrChild[0];
        
        delete tmp;
    }
    return;
}

int main(int argc, char const *argv[])
{
    
    Btree<int> t(3); // A B-Tree with minimum degree 3
  
    t.insert(1);
    t.insert(3);
    t.insert(7);
    t.insert(10);
    t.insert(11);
    t.insert(13);
    t.insert(14);
    t.insert(15);
    t.insert(18);
    t.insert(16);
    t.insert(19);
    t.insert(24);
    t.insert(25);
    t.insert(26);
    t.insert(21);
    t.insert(4);
    t.insert(5);
    t.insert(20);
    t.insert(22);
    t.insert(2);
    t.insert(17);
    t.insert(12);
    t.insert(6);
  
    cout << "Traversal of tree constructed is\n";
    t.traverse();
    cout << endl;
  
    t.remove(6);
    cout << "Traversal of tree after removing 6\n";
    t.traverse();
    cout << endl;
    
    return 0;

}
