#include <iostream>
#include <assert.h>

#define log(x) std::cout <<"[LOG]{ "<<x<<" }"<< std::endl

enum {BACKWARD, FORWARD};

template<typename T>
class PNode {
public:
    PNode *prev, *next;
    int priority;
    T value;
    PNode(T value, int priority) : value(value), priority(priority), prev(nullptr), next(nullptr){};
};


template<typename T>
class PQueue {
private:
    int max, items;
public:
    PNode<T>* first;
    PNode<T>* last;
    PQueue(int max) : max(max), items(0), first(nullptr), last(nullptr){};
    inline int getMax() const {return max;}
    inline int getItems() const {return items;}
    void insert(T value, int priority);
    void remove();
    void info(int type) const ;
};
template<typename T>
void PQueue<T>::info(int type) const {
    if(items == 0)log("sem items!"); return;
    log("--- INFO PQUEUE ---");
    PNode<T>* t;
    if(type == FORWARD){
        t = first;
        while(t){
            log(t->value <<"|"<< t->priority);
            t = t->next;
        }
    }
    if(type == BACKWARD){
        t = last;
        while(t != nullptr){
            log(t->value <<"|"<< t->priority);
            t = t->prev;
        }
    }
}

template<typename T>
void PQueue<T>::remove(){
    if(items == 0){
        log("Sem items para remover!");
        return;
    }

    PNode<T> *t = first, *h = first;
    while(t != nullptr){
        if(h->priority < t->priority)
            h = t; // pega a maior prioridade
        t = t->next;
    }

    log("Maior prioridade [ "<< h->priority <<" ]");

    if(h == first)
        first = h->next;

    if(h->next != nullptr)
        h->next->prev = h->prev;
    if(h->prev != nullptr)
        h->prev->next = h->next;

    items--;
    delete h;
}

template<typename T>
void PQueue<T>::insert(T value, int priority){
    if(items == max){
        log("numero maximo de nodos atingidos");
        return;
    }

    PNode<T>* novo = new PNode<T>(value, priority);
    if(first == nullptr)
        first = last = novo;
    else {
        PNode<T>* t;
        for(t = first; t->next; t = t->next);
        // t : ultimo nodo inserido
        t->next = novo;
        novo->prev = t;        
        last = novo;        
    }
    log(novo->value <<"|"<< novo->priority);
    items++;
}



int main(int argc, char const *argv[])
{
    PQueue<int> pq = PQueue<int>(10);
    for(int i = 0; i < 11; i++)
        pq.insert(rand()%100, rand()%10);
    pq.info(BACKWARD);
    for(int i = 0; i < 11; i++)
        pq.remove();
    pq.info(BACKWARD);
    return 0;
}
