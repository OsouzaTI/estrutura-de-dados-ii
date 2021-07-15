//============================================
// divisores de um n qualquer
//============================================
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
int main(){

    std::unique_ptr<std::vector<int>> d;
    auto f = [k=1, &d](int n) mutable -> int {
        d = std::make_unique<std::vector<int>>();
        for(k;k<n;k++)if((n%k)==0)d->push_back(k);
        return d->size();
    };

    int n;
    if(std::cin >> n)
        f(n);
    std::cout << "existem " << d->size() 
        << " divisores de "<< n << std::endl;
    std::for_each(d->begin(), d->end(), [](int n){
        std::cout<< "divisor: " <<  n << std::endl;        
    });    
    d.release();
    return 0;
}