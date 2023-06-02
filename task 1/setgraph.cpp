#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <cassert>

#include "setgraph.hpp"

SetGraph::SetGraph(int size)
: adjacencyLists(size)
{
}

SetGraph::SetGraph(const IGraph &graph)
: adjacencyLists(graph.VerticesCount())
{
    for (int from = 0; from < graph.VerticesCount(); ++from)
    {
        auto temp = graph.GetNextVertices(from);
        for (auto to: temp)
            adjacencyLists[from].insert({to, 1});
    }
}

SetGraph::~SetGraph()
{
}

void SetGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    adjacencyLists[from].insert({to, 1});
}

int SetGraph::VerticesCount() const
{
    return static_cast<int>(adjacencyLists.size());
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> nextVert;
    if (!adjacencyLists[vertex].empty())
        for (auto [key, data] : adjacencyLists[vertex])
            nextVert.push_back(key);
    std::sort(nextVert.begin(), nextVert.end());
    return nextVert;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> prevVert;
    for (size_t i = 0; i < adjacencyLists.size(); ++i)
        if (adjacencyLists[i].find(vertex) != adjacencyLists[i].end())
            prevVert.push_back(i);
    std::sort(prevVert.begin(), prevVert.end());
    return prevVert;
}