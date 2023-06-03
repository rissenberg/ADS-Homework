#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <map>

class DSU
{
public:
    DSU(size_t size)
    : parent(size), rank(size, 1)
    {
        for (int i = 0; i < size; i++)
        {
            parent[i] = i;
        }
    }
    
    size_t find_set(size_t u)
    {
        std::stack<size_t> stack;
        stack.push(u);
        
        while (parent[u] != u)
        {
            stack.push(parent[u]);
            u = parent[u];
        }
        
        size_t &root = u;
        
        while (!stack.empty())
        {
            parent[stack.top()] = root;
            stack.pop();
        }
        
        return root;
    }
    
    void union_set(size_t u, size_t v)
    {
        u = find_set(u);
        v = find_set(v);
        
        if (u != v)
        {
            if (rank[u] < rank[v])
                std::swap(u, v);
            
            parent[v] = u;
            rank[u] += rank[v];
        }
    }
    
private:
    std::vector<size_t> parent;
    std::vector<size_t> rank;
    
};

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


int MinSpanTree(const ListGraph &graph) {

    //DSU dsu(graph.VerticesCount());

    std::vector<int> d(graph.VerticesCount(), INT32_MAX);
    std::vector<short int> p(graph.VerticesCount(), -1);
    d[0] = 0;

    std::set< std::pair<int, short int> > pq;
    pq.insert({0, 0});

    while (!pq.empty()) 
    {
        unsigned short int currentVertex = pq.begin()->second;
        pq.erase(pq.begin());

		// std::cout << currentVertex << " " << p[currentVertex] << "\n";
        // for (auto i : p)
        //     std::cout << i << " ";
        // std::cout << "\n";

        for (auto& nextVertex : graph.GetNextVertices(currentVertex))
        {
            int to = nextVertex.first,
                len = nextVertex.second;
            if (len < d[to] && p[currentVertex] != to ) {
                if (pq.find({d[to], to}) != pq.end())
                    pq.erase({d[to], to});
                d[to] = len;
                p[to] = currentVertex;
                pq.insert({d[to], to});
            }
        }
    }

    int result = 0;
    for (auto i : d)
    {
        result += i;
    }

        
    return result;
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
        from--; to--;
        graph.AddEdge(from, to, length);
        graph.AddEdge(to, from, length);
    }

    std::cout << MinSpanTree(graph);

    return 0;
}