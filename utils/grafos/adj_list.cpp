#include <iostream>
#include <list>
#include <array>

class Graph {
    int V;
    std::list<int> *l;
public:
    Graph(int V);
    void addEdge(int x, int y);
    void draw();
};

Graph::Graph(int V){
    this->V = V;
    l = new std::list<int>[V];
}

void Graph::addEdge(int x, int y){
    this->l[x].push_back(y);
    this->l[y].push_back(x);
}

void Graph::draw(){
    for(int i = 0; i < V; i++){
        std::cout << "Adjacent to " << i << ": ";
        for(auto j : l[i]){
            std::cout << j << " ";
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