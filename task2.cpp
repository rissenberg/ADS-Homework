#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <queue>
#include <algorithm>
#include <functional>
#include <cassert>

struct ListGraph
{
public:
    ListGraph(int size)
    : adjacencyLists(size)
    {
    }
    
    ~ListGraph()
    {
    }
    
    void AddEdge(int from, int to) 
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
    }

    int VerticesCount() const 
    {
        return static_cast<int>(adjacencyLists.size());
    }

    std::vector<int> GetNextVertices(int vertex) const 
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }
    
    std::vector<int> GetPrevVertices(int vertex) const 
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;
        
        for (int from = 0; from < adjacencyLists.size(); from++)
        {
            for (int to: adjacencyLists[from])
            {
                if (to == vertex)
                {
                    prevVertices.push_back(from);
                }
            }
        }
        return prevVertices;
    }
    
private:
    std::vector<std::vector<int>> adjacencyLists;
};



int BFS_search(const ListGraph &graph, int vertex, int endpoint)
{
    assert(0 <= vertex && vertex < graph.VerticesCount());
    assert(0 <= endpoint && endpoint < graph.VerticesCount());
    
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::vector<int> d(graph.VerticesCount(), INT8_MAX);
    std::vector<int> k(graph.VerticesCount(), 0);
    k[vertex] = 1; d[vertex] = 0;

    std::queue<std::pair<int, int>> qu;
    for (int nextVertex: graph.GetNextVertices(vertex))
        qu.push({vertex, nextVertex});
    visited[vertex] = true;

    while (!qu.empty())
    {
        auto edge = qu.front();
        int prevVertex = std::get<0>(edge);
        int currentVertex = std::get<1>(edge);
        qu.pop();
        
        if (d[prevVertex] + 1 < d[currentVertex])
        {
            d[currentVertex] = d[prevVertex] + 1;
            k[currentVertex] = k[prevVertex];
        } else
        if (d[prevVertex] + 1 == d[currentVertex])
            k[currentVertex] += k[prevVertex];
        
        if (!visited[currentVertex])
            for (int nextVertex: graph.GetNextVertices(currentVertex))
            {
                if (!visited[nextVertex])
                    qu.push({currentVertex, nextVertex});
            }
        visited[currentVertex] = true;

    }
    
    return k[endpoint];
}


int main(int argc, const char * argv[]) {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int v, n;

    std::cin >> v >> n;

    ListGraph graph(v);

    for (int i = 0; i < n; ++i)
    {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    int path_from, path_to;
    std::cin >> path_from >> path_to;

    std::cout << BFS_search(graph, path_from, path_to) << " ";

    return 0;
}
