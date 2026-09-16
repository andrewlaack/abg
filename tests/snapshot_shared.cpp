#include "../include/graph.hpp"
#include <catch2/catch_test_macros.hpp>
#include "../include/prim.hpp"
#include <queue>
#include <unordered_set>

Graph basicGraphSerialization() {
    srand(42);
    int vertCount = 10;
    int edgeCount = 10;
    float xMax = 10;
    float yMax = 10;
    auto g = Graph(edgeCount,vertCount,xMax,yMax);
    return g;
}

Graph fullTraversalSerialization() {
    srand(42);
    std::size_t edgeCount = 1;
    std::size_t vertCount = 2;

    float xMax = 5120;
    float yMax = 1440;

    Graph g = Graph(edgeCount, vertCount, xMax,yMax);
    std::unordered_set<std::size_t> visitedIndices {};
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> toVisit {};
    std::vector<Edge> edges = g.getEdgesOfVertexIdx(0);

    for(auto edge: edges) {
        toVisit.push(edge);
    }

    g.traverseVertexIdx(0);
    visitedIndices.insert(0);

    while (toVisit.size() != 0) {
        oneStepPrim(toVisit, visitedIndices, g);
    }
    
    return g;
}
