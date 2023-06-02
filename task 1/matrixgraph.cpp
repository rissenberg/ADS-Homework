#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <cassert>

#include "matrixgraph.hpp"

MatrixGraph::MatrixGraph(int size)
{
    adjacencyLists.resize(size);
    for (int i = 0; i < size; ++i)
        adjacencyLists[i].resize(size);
}

MatrixGraph::MatrixGraph(const IGraph &graph)
{ 
    int size = graph.VerticesCount();
    adjacencyLists.resize(size);
    for (int i = 0; i < size; ++i)
        adjacencyLists[i].resize(size);
    for (int from = 0; from < size; ++from)
    {
        auto temp = graph.GetNextVertices(from);
        for (size_t to = 0; to < temp.size(); ++to)
            adjacencyLists[from][temp[to]] = 1;
    }
}

MatrixGraph::~MatrixGraph()
{
}

void MatrixGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    adjacencyLists[from][to] = 1;
}

int MatrixGraph::VerticesCount() const
{
    return static_cast<int>(adjacencyLists.size());
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> nextVert;
    for (int i = 0; i < int(adjacencyLists[vertex].size()); ++i)
        if (adjacencyLists[vertex][i])
            nextVert.push_back(i);
    return nextVert;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> prevVert;
    for (int i = 0; i < int(adjacencyLists.size()); ++i)
        if (adjacencyLists[i][vertex])
            prevVert.push_back(i);
    return prevVert;
}

