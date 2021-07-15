//============================================
// primo ou nao
//============================================
#include <iostream>


int main(){

    auto primo = [](int n) mutable {
        int k = 0, j = 0;
        while(k < (n/2)){            
            if((n % (++k))==0){
                std::cout << k << std::endl;
                j++;
            }
        }
        return j <= 1;
    };

    int n;
    while(std::cin >> n){
        if(primo(n))
            std::cout << "e primo" << std::endl;
        else
            std::cout << "nao e primo" << std::endl;
    }
    return 0;
}