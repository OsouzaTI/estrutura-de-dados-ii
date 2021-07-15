//============================================
// tabuada de qualquer numero
//============================================
#include <iostream>
#include <vector>
#include <array>
#include <functional>

using operation = std::function<int(int, int)>;
using evaluator = std::function<int(int, int, operation)>;
enum e_operacao
{
    SOMA,
    SUBTRACAO,
    MULTIPLICACAO,
    DIVISAO
};

const int max_size = 10;

int main()
{

    evaluator eval = [](int a, int b, operation op)
    { return op(a, b); };
    auto fsoma = [](int a, int b)
    { return a + b; };
    auto fsub = [](int a, int b)
    { return a - b; };
    auto fmult = [](int a, int b)
    { return a * b; };
    auto fdiv = [](int a, int b)
    { return (int)a / b; };
    auto tabuada = [&eval, &fsoma, &fsub, &fmult, &fdiv](int n, e_operacao type) mutable
    {
        auto _s = [k = 0, n, &eval, &fsoma]() mutable
        {
            while ((k++) < max_size)
                std::cout << k << "+" << n << "=" << eval(k, n, fsoma) << std::endl;
        };

        auto _sb = [k = 0, n, &eval, &fsub]() mutable
        {
            while ((k++) < max_size)
                std::cout << k << "-" << n << "=" << eval(k, n, fsub) << std::endl;
        };

        auto _mt = [k = 0, n, &eval, &fmult]() mutable
        {
            while ((k++) < max_size)
                std::cout << k << "*" << n << "=" << eval(k, n, fmult) << std::endl;
        };

        auto _d = [k = 0, n, &eval, &fdiv]() mutable
        {
            while ((k++) < max_size)
                std::cout << k << "/" << n << "=" << eval(k, n, fdiv) << std::endl;
        };

        switch (type)
        {
            case SOMA:
                _s();
                break;
            case SUBTRACAO:
                _sb();
                break;
            case MULTIPLICACAO:
                _mt();
                break;
            case DIVISAO:
                _d();
                break;
        }

    };

    int n;
    if (std::cin >> n)
        tabuada(n, MULTIPLICACAO);

    return 0;
}