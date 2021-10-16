#include <iostream>
#include <vector>
#include <algorithm>

int main(){

    int nEntradas;
    std::string entrada, saida;
    while(std::cin >> nEntradas && nEntradas != 0){
        std::vector<std::string> palavras;

        // pegando as entradas
        int i;
        for(i = 0; i < nEntradas; i++){
            std::cin >> entrada;
            palavras.push_back(entrada); 
        }

        // ordenando por ordem lexical
        std::sort(palavras.begin(), palavras.end(),
            [](std::string a, std::string b){
                return a < b;
            }
        );

        saida = "Conjunto Bom";

        for(i = 0; i < palavras.size() - 1; i++){

            std::string pA = palavras[i];
            std::string pB = palavras[i+1];

            if(pB.rfind(pA, 0) == 0){
                saida = "Conjunto Ruim";
            }        

        }
        
        std::cout << saida << std::endl;

    }

    return 0;
}