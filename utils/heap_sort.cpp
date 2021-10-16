#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// levando em consideracao o
// array comecando em 0
#define L(i) 2*i+1
#define R(i) 2*i+2

using std::cin;
using std::cout;
using std::string;

void heapify(std::vector<string>& arr, int n, int i) {

    int l = L(i);
    int r = R(i);
    int maior = i;
    
    if(l < n && arr[l] > arr[maior])
        maior = l;
    
    if(r < n && arr[r] > arr[maior])
        maior = r;
    
    if(maior != i) {
        std::swap(arr[i], arr[maior]);
        heapify(arr, n, maior);
    }

}

void heapSort(std::vector<string>& arr) {
    int n = arr.size();
    for(int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    for(int i = n-1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }

}

template<typename T>
void printVector(std::vector<T> &v) {
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << std::endl;
}

int main(int argc, char const *argv[])
{
    std::vector<std::tuple<string, int, bool>> nomes;
    string nome, resposta;
    int ordem = -1;
    while(cin >> nome) {
        if(nome == "FIM")break;
        cin >> resposta;
        auto res = std::make_tuple(nome, ++ordem, (resposta == "YES"));
        nomes.push_back(res);
    }   

    std::vector<string> vSim;
    std::vector<string> vNao;
    bool exists;

    int vencedorOrdem       = -1;
    int maiorNumeroDeLetras = -1;
    string vencedor;
    // separando os nomes em dois vetores
    std::for_each(nomes.begin(), nomes.end(), [&](auto &nome) {
        
        string nomeAtual = std::get<0>(nome);
        int ordem        = std::get<1>(nome);
        bool resposta    = std::get<2>(nome);

        if(resposta){   
            int numeroDeLetras = nomeAtual.size();                  
            if(numeroDeLetras > maiorNumeroDeLetras){                
                maiorNumeroDeLetras = numeroDeLetras;
                vencedor = nomeAtual;
                vencedorOrdem = ordem;                    
            } else if(numeroDeLetras == maiorNumeroDeLetras) {
                if(ordem < vencedorOrdem){
                    vencedor = nomeAtual;
                    vencedorOrdem = ordem;                    
                }
            }
            // se o nome ja existe no vetor de sim
            exists = std::find(vSim.begin(), vSim.end(), nomeAtual) != vSim.end();
            if(!exists)vSim.push_back(nomeAtual);
        } else { // se tiver respondido nao
            // se o nome ja existe no vetor de nao
            exists = std::find(vNao.begin(), vNao.end(), nomeAtual) != vNao.end();
            if(!exists)vNao.push_back(nomeAtual);
        }
    });
    heapSort(vSim);
    heapSort(vNao);
    printVector(vSim);
    printVector(vNao);
    cout << std::endl;
    cout << "Amigo do Habay:" << std::endl;
    cout << vencedor << std::endl;
    return 0;
}
