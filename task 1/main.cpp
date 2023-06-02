#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <cassert>

#include "igraph.cpp"
#include "listgraph.cpp"
#include "matrixgraph.cpp"
#include "setgraph.cpp"
#include "arcgraph.cpp"


int main(int argc, const char * argv[]) {

    freopen("output.txt", "w", stdout);
    
    ListGraph listGraph(9);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);
    listGraph.AddEdge(7, 8);
    
    std::cout << "ListGraph:\n";
    BFS(listGraph, [](int vertex){ 
        std::cout << vertex << " "; 
    });
    std::cout << "\n";

    DFS(listGraph, [](int vertex){ 
        std::cout << vertex << " "; 
    });
    std::cout << "\n";

    for (int vertex: topologicalSort(listGraph))
    {
        std::cout << vertex << " ";
    }
    std::cout << "\n\n";

    // Нужно продемонстрировать работу конструктора копирования, проинициализировав
    // графы разных классов друг от друга. Далее, показать, что вершины и ребра
    // успешно скопированы: число вершин осталось прежним, произвести BFS и DFS.
    // MatrixGraph
    
    MatrixGraph matrixGraph(listGraph);

    std::cout << "MatrixGraph:\n";
    BFS(matrixGraph, [](int vertex){ 
        std::cout << vertex << " "; 
    });
    std::cout << "\n";

    DFS(matrixGraph, [](int vertex){ 
        std::cout << vertex << " "; 
    });
    std::cout << "\n";

    for (int vertex: topologicalSort(matrixGraph))
    {
        std::cout << vertex << " ";
    }
    std::cout << "\n\n";

    // ArcGraph
    ArcGraph arcGraph(matrixGraph);

    std::cout << "ArcGraph:\n";
    BFS(arcGraph, [](int vertex){ 
        std::cout << vertex << " "; 
    });
    std::cout << "\n";

    DFS(arcGraph, [](int vertex){ 
        std::cout << vertex << " "; 
    });
    std::cout << "\n";

    for (int vertex: topologicalSort(arcGraph))
    {
        std::cout << vertex << " ";
    }
    std::cout << "\n\n";

    // SetGraph
    SetGraph setGraph(arcGraph);

    std::cout << "SetGraph:\n";
    BFS(setGraph, [](int vertex){ 
        std::cout << vertex << " "; 
    });
    std::cout << "\n";

    DFS(setGraph, [](int vertex){ 
        std::cout << vertex << " "; 
    });
    std::cout << "\n";

    for (int vertex: topologicalSort(setGraph))
    {
        std::cout << vertex << " ";
    }
    std::cout << "\n";
    
    return 0;
}

/* output.txt:

ListGraph:
0 1 5 2 3 6 4 7 8 
0 1 2 3 4 6 5 7 8 
7 8 0 1 5 3 6 4 2 

MatrixGraph:
0 1 5 2 3 6 4 7 8 
0 1 2 3 4 6 5 7 8 
7 8 0 1 5 3 6 4 2 

ArcGraph:
0 1 5 2 3 6 4 7 8 
0 1 2 3 4 6 5 7 8 
7 8 0 1 5 3 6 4 2 

SetGraph:
0 1 5 2 3 6 4 7 8 
0 1 2 3 4 6 5 7 8 
7 8 0 1 5 3 6 4 2 

*/