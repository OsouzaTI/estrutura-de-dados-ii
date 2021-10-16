#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

void SomaDeImparesConsecutivos(int x, int y) {
    if(x > y)
        swap(x, y);

    int soma = 0;
    for (int i = x+1; i < y; i++) {
        if (i % 2 != 0) {
            soma += i;
        }
    }
    cout << soma << endl;
}

int main(){
    
    int x, y, n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> x >> y;  
        SomaDeImparesConsecutivos(x, y);
    }

    return 0;
}