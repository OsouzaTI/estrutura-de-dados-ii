#include <iostream>
#include <vector>

// levando em consideracao o
// array comecando em 0
#define P(i) (i-1) / 2
#define L(i) 2*i+1
#define R(i) 2*i+2

template <typename T>
class Heap {
    private:
        std::vector<T> A;
        int size;
        void heapify(int i);
        void buildHeap();
        void swap(T* a, T* b);
    public:
        Heap();
        Heap(std::vector<T> v);
        void insert(T value);
        T remove();
        void print();
        void printHeapTree(Heap<int> h, int i, int level);
};

template <typename T>
Heap<T>::Heap() {
    size = 0;
}

template <typename T>
Heap<T>::Heap(std::vector<T> v) {
    size = v.size();
    A = v;
    buildHeap();
}

template <typename T>
void Heap<T>::print() {
    for (int i = 0; i < size; i++) {
        std::cout << A[i] << " ";
    }
}

template <typename T>
void Heap<T>::swap(T* a, T* b) {
    T aux = *a;
    *a = *b;
    *b = aux;
}

template <typename T>
void Heap<T>::heapify(int i) {
    int l = L(i);
    int r = R(i);
    int maior = i;
    if (l < size && A[l] > A[i])
        maior = l;
    if (r < size && A[r] > A[maior])
        maior = r;
    if (maior != i) {
        swap(&A[i], &A[maior]);
        heapify(maior);
    }
}

template <typename T>
void Heap<T>::insert(T value) {
    A.resize(A.size() + 1); // alocando mais um elemento 
    int i  = A.size() - 1;
    while( i > 0 && A[P(i)] < value){
        A[i] = A[P(i)];
        i = P(i);
    }
    A[i] = value;
    size++;
}

template <typename T>
T Heap<T>::remove() {
    T key = A[0];
    A[0] = A[size - 1];
    A.resize(size - 1);
    heapify(0);
    size--;
    return key;
}

template <typename T>
void Heap<T>::buildHeap() {
    for (int i = size / 2; i >= 0; i--) {
        heapify(i);
    }
}

template <typename T>
void Heap<T>::printHeapTree(Heap<int> h, int i, int level) {
    if (i < h.size) {
        printHeapTree(h, R(i), level + 1);
        for (int j = 0; j < level; j++) {
            std::cout << "   ";
        }
        std::cout << h.A[i] << std::endl;
        printHeapTree(h, L(i), level + 1);
    }
}

int main(int argc, char const *argv[])
{
    
    std::vector<int> data =  { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 };    
    Heap<int> heap(data);
    heap.printHeapTree(heap, 0, 2);
    heap.remove();
    heap.printHeapTree(heap, 0, 2);

    return 0;
}
