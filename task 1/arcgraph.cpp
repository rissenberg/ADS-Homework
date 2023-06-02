#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <cassert>

#include "arcgraph.hpp"

ArcGraph::ArcGraph(int size)
: vertCount(size)
{
}

ArcGraph::ArcGraph(const IGraph &graph)
: vertCount(graph.VerticesCount())
{ 
    for (int from = 0; from < graph.VerticesCount(); ++from)
    {
        auto temp = graph.GetNextVertices(from);
        for (size_t to = 0; to < temp.size(); ++to)
            edgesList.push_back({from, temp[to]});                
    }
}

ArcGraph::~ArcGraph()
{
}

void ArcGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < vertCount);
    assert(0 <= to && to < vertCount);
    edgesList.push_back({from, to});
}

int ArcGraph::VerticesCount() const
{
    return vertCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < vertCount);
    std::vector<int> nextVert;
    for (size_t i = 0; i < edgesList.size(); ++i)
        if (std::get<0>(edgesList[i]) == vertex)
            nextVert.push_back(std::get<1>(edgesList[i]));
    return nextVert;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < vertCount);
    std::vector<int> prevVert;
    for (size_t i = 0; i < edgesList.size(); ++i)
        if (std::get<1>(edgesList[i]) == vertex)
            prevVert.push_back(std::get<0>(edgesList[i]));
    return prevVert;
}