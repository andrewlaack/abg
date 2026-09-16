#include "../headers/prim.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstddef>

TEST_CASE( "Small Prim algorithm", "[small prim algo]" ) {
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
    // this will be true bc 2 vertices 1 edge...
    // our graph may have multi-edges.
    REQUIRE(visitedIndices.size() == 2);
}


bool isConnected(Graph g) {

    std::unordered_set<std::size_t> verticesFound {0};

    std::vector<std::size_t> current {};

    while(true) {
        for(auto key: verticesFound) {
            auto edges = g.getEdgesOfVertexIdx(key);
            for(auto edge: edges) {
                current.push_back(edge.v1Index);
                current.push_back(edge.v2Index);
            }
        }
        std::size_t len = verticesFound.size();
        for(auto idx: current) {
            verticesFound.insert(idx);
        }
        if (len == verticesFound.size()) {
            break;
        }
    }

    return verticesFound.size() == g.getVertexCount();
}


TEST_CASE( "Large Prim algorithm", "[Large prim algo]" ) {
    std::size_t edgeCount = 3000;
    std::size_t vertCount = 1000;

    float xMax = 5120;
    float yMax = 1440;

    Graph g = Graph(edgeCount, vertCount, xMax,yMax);
    std::unordered_set<std::size_t> visitedIndices {};
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> toVisit {};

    do {
        g = Graph(edgeCount, vertCount, xMax,yMax);
    }
    while(!isConnected(g));


    g.traverseVertexIdx(0);
    visitedIndices.insert(0);

    std::vector<Edge> edges = g.getEdgesOfVertexIdx(0);

    for(auto edge: edges) {
        toVisit.push(edge);
    }

    while (toVisit.size() != 0) {
        oneStepPrim(toVisit, visitedIndices, g);
    }

    REQUIRE(visitedIndices.size() == vertCount);
}

TEST_CASE( "Medium Prim algorithm", "[Medium prim algo]" ) {
    std::size_t edgeCount = 70;
    std::size_t vertCount = 51;

    float xMax = 5120;
    float yMax = 1440;

    Graph g = Graph(edgeCount, vertCount, xMax,yMax);
    std::unordered_set<std::size_t> visitedIndices {};
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> toVisit {};

    do {
        g = Graph(edgeCount, vertCount, xMax,yMax);
    }
    while(!isConnected(g));


    g.traverseVertexIdx(0);
    visitedIndices.insert(0);

    std::vector<Edge> edges = g.getEdgesOfVertexIdx(0);

    for(auto edge: edges) {
        toVisit.push(edge);
    }

    while (toVisit.size() != 0) {
        oneStepPrim(toVisit, visitedIndices, g);
    }

    REQUIRE(visitedIndices.size() == vertCount);
}


TEST_CASE( "Staircase Prim algorithm", "[Staircase prim algo]" ) {
    for(int i = 2; i < 30; ++i) {
        for(int x = i-1; x < 60; ++x) {
            std::size_t edgeCount = x;
            std::size_t vertCount = i;

            float xMax = 5120;
            float yMax = 1440;

            Graph g = Graph(edgeCount, vertCount, xMax,yMax);
            std::unordered_set<std::size_t> visitedIndices {};
            std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> toVisit {};

            do {
                g = Graph(edgeCount, vertCount, xMax,yMax);
            }
            while(!isConnected(g));


            g.traverseVertexIdx(0);
            visitedIndices.insert(0);

            std::vector<Edge> edges = g.getEdgesOfVertexIdx(0);

            for(auto edge: edges) {
                toVisit.push(edge);
            }

            while (toVisit.size() != 0) {
                oneStepPrim(toVisit, visitedIndices, g);
            }

            REQUIRE(visitedIndices.size() == vertCount);


        }
    }
}

