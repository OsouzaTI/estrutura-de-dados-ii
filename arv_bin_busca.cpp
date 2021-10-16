#include <iostream>

using namespace std;
#define COUNT 10

//Estrutura do nó
class Node {
    public:
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node *root, int data) {
    if(root == NULL) return newNode(data);

    if(data < root->data)
        root->left = insert(root->left, data);
    else if(data > root->data)
        root->right = insert(root->right, data);
    
    return root;
}

Node* find(Node *root, int data) {
    if(root == NULL) return NULL;
    if(data == root->data) return root;

    if(data < root->data)
        root->left = find(root->left, data);
    else if(data > root->data)
        root->right = find(root->right, data);
    
    // return root;
}


void printfTree(Node *root) {
    if(root != NULL) {
        cout << root->data << "";
        cout << "(";
        printfTree(root->left);
        printfTree(root->right);
        cout << ")";        
    }
}

//pré-ordem (R-E-D)
void preOrder(Node *root) {
    if(root != NULL) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);        
    }
}

//in-ordem (E-R-D)
void inOrder(Node *root) {
    if(root != NULL) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);        
    }
}

//pos-ordem (E-D-R)
void posOrder(Node *root) {
    if(root != NULL) {
        posOrder(root->left);
        posOrder(root->right);      
        cout << root->data << " ";  
    }
}

void print2D(Node *root, int space) {
    if (root == NULL) return;
     // Increase distance between levels
    space += COUNT;
    print2D(root->right, space);
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout << root->data << endl;
    print2D(root->left, space);
}

int main() {

    Node *root = NULL; //arvore vazia
    root = insert(root, 12);
    insert(root, 50);
    insert(root, 48);
    insert(root, 5);
    insert(root, 84);
    insert(root, 25);
    
    printfTree(root);
    cout << endl;

    // print2D(root, 0);
    // cout << endl;

    //Percursos na árvore
    // preOrder(root);
    // cout << endl;
    // inOrder(root);
    // cout << endl;
    // posOrder(root);
    // cout << endl;

    // Busca elemento
    Node* x = find(root, 99);
    if(x)
        cout << "Encontrou: " << x->data << endl;
    else 
        cout << "Não está na arvore!" << endl;

    return 0;
}