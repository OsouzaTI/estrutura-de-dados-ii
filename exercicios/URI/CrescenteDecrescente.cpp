#include <iostream>
using namespace std;

void crescenteOuDecrescente(int x, int y) {
    std::string r = (x < y) ? "Crescente" : "Decrescente";
    cout << r << endl;
}


int main(){
    int a, b;
    while(true){
        cin >> a >> b;
        if(a != b)
            crescenteOuDecrescente(a, b);
        else break;
    }
    return 0;
}