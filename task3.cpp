#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>
#include <cassert>

struct ListGraph
{
public:
    ListGraph(unsigned short int& size)
    : adjacencyLists(size)
    {
    }
    
    ~ListGraph()
    {
    }
    
    void AddEdge(unsigned short int& from, unsigned short int& to, int& length) 
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back({to, length});
    }

    int VerticesCount() const 
    {
        return static_cast<int>(adjacencyLists.size());
    }

    std::vector<std::pair<unsigned short int, int>> GetNextVertices(unsigned short int& vertex) const 
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<unsigned short int> nextVert;
        return adjacencyLists[vertex];
    }
    
    int GetLength (int from, int to) const
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        for (auto [key, data] : adjacencyLists[from])
            if (key == to)
                return data;
        return 0;
    }
    
private:
    std::vector<std::vector<std::pair<unsigned short int, int>>> adjacencyLists;

};


int minpath_search(const ListGraph &graph, unsigned short int& vertex, unsigned short int& endpoint)
{
    assert(0 <= vertex && vertex < graph.VerticesCount());
    assert(0 <= endpoint && endpoint < graph.VerticesCount());

    std::vector<int> d(graph.VerticesCount(), INT32_MAX);
    d[vertex] = 0;

    std::queue<unsigned short int> qu;
    qu.push(vertex);

    while (!qu.empty()) 
    {
        unsigned short int currentVertex = qu.front();
        qu.pop();

        for (auto& it: graph.GetNextVertices(currentVertex)) 
        {
            unsigned short int nextVertex = std::get<0>(it);
            int len = std::get<1>(it);

            if (d[nextVertex] > d[currentVertex] + len) 
            {
                d[nextVertex] = d[currentVertex] + len;
                qu.push(nextVertex);
            }
        }
    }
    return d[endpoint];
}


int main(int argc, const char * argv[]) {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    unsigned short int v;
    int n;

    std::cin >> v >> n;

    ListGraph graph(v);

    for (int i = 0; i < n; ++i)
    {
        unsigned short int from, to;
        int length;
        std::cin >> from >> to >> length;
        graph.AddEdge(from, to, length);
        graph.AddEdge(to, from, length);
    }

    unsigned short int path_from, path_to;
    std::cin >> path_from >> path_to;

    std::cout << minpath_search(graph, path_from, path_to);

    return 0;
}
