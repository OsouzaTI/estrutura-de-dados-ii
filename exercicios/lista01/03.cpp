//============================================
//  Fatorial de 0 existe?
//============================================
#include <iostream>
#include <functional>

int main(){

    auto print = [](int a, int b){
        std::cout << "o fatorial de "
            << a << " e " << b << ".";
    };

    std::function<int(int)> f;
    f = [&f](int n){
        if(n == 0)
            return 1; // existe kkk indio burrão
        else
            return n * f(n-1);
    };
    int n;
    if(std::cin >> n)print(n, f(n));
    return 0;
}