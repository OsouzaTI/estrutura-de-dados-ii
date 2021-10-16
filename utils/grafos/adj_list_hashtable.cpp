#include <iostream>
#include <list>
#include <map>
#include <unordered_map>
#include <cstring>
#include <utility>

using graph_pair_t  = std::pair<std::string, int>;
using graph_list_t  = std::list<graph_pair_t>;

class Graph {
    // std::unordered_map<std::string, std::list<graph_pair_t>> l;
    std::map<std::string, graph_list_t> l;
public:
    Graph(int V);
    void addEdge(std::string x, std::string y, int wt, bool bd = true);
    void draw();
};

Graph::Graph(int V){

}

void Graph::addEdge(std::string x, std::string y, int wt, bool bd){
    this->l[x].push_back(std::make_pair(y, wt));
    if(bd)this->l[y].push_back(std::make_pair(x, wt));
}

void Graph::draw(){
    for( auto& u : l){
        std::string key = u.first;
        graph_list_t adjs = u.second;
        std::cout << key << ": ";
        for( auto& v : adjs){
            std::cout << v.first << "(" << v.second << ") ";
        }
        std::cout << std::endl;
    } 
}

int main(){
    Graph g(5);
    g.addEdge("A", "B", 6, false);
    g.addEdge("A", "E", 1);
    g.addEdge("E", "C", 3);
    g.addEdge("D", "C", 2, false);
    g.addEdge("D", "E", 4);
    g.addEdge("B", "D", 8);

    g.draw();
}