//============================================
//  fibonnaci
//============================================
#include <iostream>
#include <functional>

int main(){
    
    auto print = [](int x){
        std::cout << x << std::endl;
    };

    std::function<int(int,int,int)> fib;
    fib = [t=0, s=0, &print, &fib](int a, int b, int n) mutable {
        int _temp = a;
        print(a);
        s += a; a = b; b += _temp;
        return ((t++) < n) ? fib(a, b, n) : s;
    };

    int n;
    if(std::cin>>n)
        std::cout << "A soma de "<< n << " termos :" << fib(0, 1, n);

    return 0;
}