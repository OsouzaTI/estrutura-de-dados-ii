#include <iostream>

using std::cout;
using std::endl;
using std::cin;

struct Pair {
    bool bit;
    int key;
    int value;
    Pair() : bit(false){}; 
    void info(){
        cout << "Key: " << this->key << " Value: " << this->value << "\n";
    }
};
typedef Pair Pair;

void display(Pair ht[], int size) {
    int i;
    cout << "Key\tValue\n";
    for(i=0; i<size; i++)
        cout<<"[" << ht[i].bit << "]"
            << ht[i].key 
            << "\t" 
            << ht[i].value
            << "\n";
}

int hash(int key, int N){
    return key % N;
}

Pair* search(Pair ht[], int key, int N){
    int h = hash(key, N);
    int i = 0;
    while(ht[h].key != key){
        if((i++) > N)
            return nullptr;
        h = (h + 1) % N;
    }
    return &ht[h];
}

void remove(Pair ht[], int key, int N){
    Pair* p = search(ht, key, N);
    p->bit      = false;
    p->key      = 0;
    p->value    = 0;
    // removido CARALHO
}

int main() {
    int size, i, el;
    cout << "Enter the size of the table: ";
    cin >> size;
    Pair hash_table[size];
    cout << "Enter the elements: \n";
    for(i=0; i < size; i++) {
        cin >> el;
        int h = hash(el, size);        
        while(hash_table[h].bit)    // tratamento das colisoes
            h = (h + 1) % size;     // incremento circular
        // nesse ponto 'h' e um indice de um espaco vago
        // na tabela de hash
        hash_table[h].bit   = true;
        hash_table[h].value = rand()%100;
        hash_table[h].key   = el;
    }
    cout << endl;
    display(hash_table, size);

    // pesquisa
    Pair* p = search(hash_table, 5, size);
    if(p)p->info();

    // removendo
    remove(hash_table, 43, size);

    display(hash_table, size);

}