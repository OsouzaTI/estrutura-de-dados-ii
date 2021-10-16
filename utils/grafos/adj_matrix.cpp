#include <iostream>
#include <vector>

using matrix_t = std::vector<std::vector<int>>;

class Graph {
    int V;
    matrix_t matrix;
public:
    Graph(int V);
    void addEdge(int x, int y);
    void draw();
};

Graph::Graph(int V){
    this->V = V;
    
    for(int i = 0; i < V; i++){
        matrix.push_back(std::vector<int>());
        for(int j = 0; j < V; j++){
            matrix[i].push_back(0);
        }
    }

}

void Graph::addEdge(int x, int y){
    this->matrix[x][y] = 1;
}

void Graph::draw(){
    int i, j;
    for(i = 0; i < V; i++){
        for(j = 0; j < V; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(){
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(0, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.draw();
}