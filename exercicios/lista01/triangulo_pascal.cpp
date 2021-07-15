//============================================
// triangulo de pascal
//============================================
#include <iostream>
#include <vector>
#include <functional>

int main(){
    
    int pos = 10;
    std::function<void(int, std::vector<int>)> tPascal;

    tPascal = [n = 0, &tPascal](int depth, std::vector<int> ant) mutable {
        if(depth < 0)return;
        std::vector<int> _temp{};
        for(int _n = 0; _n <= n; _n++){
            int _v;
            if(_n == 0 || _n == n) {
                _temp.push_back(1);
                std::cout << 1 << "\t";
            } else {
                _v = ant[_n-1] + ant[_n];
                _temp.push_back(_v);
                std::cout << _temp[_n] << "\t";
            }
        }
        std::cout << "\n";
        n++;
        tPascal(depth - 1, _temp);
    };

    tPascal(8, {});

    return 0;
}