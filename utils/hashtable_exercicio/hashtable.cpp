#include <iostream>

// find primo
int genPrimeNumber(int base){
    /*
        sera procurado um numero
        primo com pelo menos o dobro
        do tamanho de 'base'
    */


    int i,
        divisores,
        li = base * 2,
        lf = (base * 3);
    for(i = li; i < lf; i++){
        divisores = 0;
        int j, alvo = i;
        for(j = 1; j <= i; j++){
            if(i % j == 0){
                divisores++;
            }
        }
        if(divisores == 2)
            return i;
    }

    return -1;
}


class HTable {

private:

    struct HNode {
        bool bit; // verifica se ja foi encontrado por algum hash
        int data;
        HNode* n;
        HNode() : bit(false), data(0), n(nullptr) {};
        void operator=(const HNode& other){
            this->bit  = other.bit;
            this->data = other.data;
            this->n    = other.n; 
        }
    };

    // Tamanho inicial da tabela
    int size; 
    int items;
    int collisions;
    // representacao da tabela hash
    HNode* table = nullptr;
    
    int hash_A(int n){ return n % size; }
    int hash_B(int n){ return size - 2 - n%(size - 2); }
    void resize();

public:
    HTable(int size);
    void insert(int key);
    void info();

};

HTable::HTable(int size){
    this->size  = size; 
    items       = 0;
    collisions  = 0;
    table       = new HNode[size];
}

void HTable::resize(){
    std::cout << "Tamanho da tabela hash chegou a 75%\n";
    int oldSize = size; // valor antido do tamanho
    size *= 1.947; // alterando o tamanho por um fator fracionario

    HNode* nTable = new HNode[size];
    // copiando a antiga tabela de hash
    int i;
    for(i = 0; i < oldSize; i++)
        nTable[i] = table[i];  
    table = nTable;
}

void HTable::insert(int key){

    if( (items / size) > .75 )
        resize(); // aumenta o tamanho da tabela hash com 75% cheia

    int hA = hash_A(key);
    int hB = hash_B(key);
    int h  = (hA + hB) % size;
    if(table[h].bit){ // caso ja exista informação aqui
        collisions++; // colisoes
        
        HNode* no = new HNode();
        no->bit  = true;
        no->data = key;
        no->n    = nullptr;

        if(!table[h].n) {
            table[h].n = no;
        } else {
            // procurando o ultimo no
            HNode* t = table[h].n;
            for(t;  t->n; t = t->n);        
            t->n = no;
        }

    } else { // caso seja a primeira ocorrencia
        table[h].bit = true;
        table[h].data = key;
        table[h].n = nullptr; 
    }

    items++;
}

void HTable::info(){
    std::cout << "Colisoes: " << collisions << std::endl;
    for(int i  = 0; i < size; i++){
        std::cout <<"table[" << i << "]" << " = " << table[i].data << std::endl;
        std::cout <<"\tColisoes: ";
        HNode* t = table[i].n;
        while(t){
            std::cout <<"["<< t->data << "]";
            t = t->n;
        }
        std::cout << std::endl;
    }
}



int main(){

    HTable h = HTable(13);
    for(int i = 0; i < 120; i++)
        h.insert((rand()%1250));

    h.info();
    return 0;
}