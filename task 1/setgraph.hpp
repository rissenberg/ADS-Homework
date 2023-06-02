#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <cassert>

#include "igraph.cpp"

struct SetGraph: public IGraph
{
public:
    SetGraph(int size);
    
    SetGraph(const IGraph &graph);
    
    ~SetGraph();
    
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    
    std::vector<int> GetPrevVertices(int vertex) const override;
    
private:
    std::vector<std::unordered_map<int, bool>> adjacencyLists;

};