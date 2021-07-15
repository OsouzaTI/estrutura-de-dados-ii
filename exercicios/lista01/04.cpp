//============================================
// menor inteiro positivo cujo o quadrado é 
// superior a um valor L dado
//============================================
#include <iostream>


int main(){
    
    auto sqr  = [](int x){return x*x;};

    int l;
    if(std::cin >> l){
        int n = 0;
        while(sqr(n++) <= l);
        std::cout << "x: " << n-1 << std::endl;
    }

    return 0;
}