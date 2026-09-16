#include "../headers/graph.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <unordered_set>

TEST_CASE( "Graph traversal invariants", "[graph traversal]" ) {
    int vertCount = 10;
    int edgeCount = 10;
    float xMax = 10;
    float yMax = 10;
    auto g = Graph(edgeCount,vertCount,xMax,yMax);
    int count = 0;
    for(int i = 0; i < vertCount; ++i) {
        g.traverseVertexIdx(i);
        count += 1;
    }
    for(int i = 0; i < vertCount; ++i) {
        REQUIRE(g.getVertex(i).visited);
    }
    
    bool error = false;

    try {
        g.getVertex(vertCount + 1);
    } catch (std::invalid_argument e) {
        error = true;
    }

    REQUIRE(error);
}

void createGraph(int vertCount, int edgeCount) {
    auto g = Graph(edgeCount,vertCount,10,10);
}

TEST_CASE( "Graph gracefully handles stupid fucking inputs", "[graph bad inputs]" ) {
    int vertCount = 0;
    int edgeCount = 0; // some trivial and stupid graph
    
    bool error = false;

    try {
        createGraph(vertCount, edgeCount);
    } catch (std::invalid_argument e) {
        error = true;
    }
    REQUIRE(!error);

    vertCount = 0;
    edgeCount = 1; // bad

    error = false;
    try {
        createGraph(vertCount, edgeCount);
    } catch (std::invalid_argument e) {
        error = true;
    }

    REQUIRE(error);

}

TEST_CASE( "Graph respects max x and max y values", "[graph max values]" ) {
    int vertCount = 10;
    int edgeCount = 10;

    for(int z = 2; z < 100; ++z) {

        float xMax = 0;
        float yMax = 0;

        while (xMax == 0 || yMax == 0) {
            xMax = rand() % z;
            yMax = rand() % z;
        }

        auto g = Graph(edgeCount,vertCount,xMax,yMax);

        for(int i = 0; i < vertCount; ++i) {
            REQUIRE(g.getVertex(i).position.x <= xMax);
        }
        for(int i = 0; i < vertCount; ++i) {
            REQUIRE(g.getVertex(i).position.y <= yMax);
        }
    }
        auto g = Graph(edgeCount,vertCount,UINT32_MAX,UINT32_MAX);

        for(int i = 0; i < vertCount; ++i) {
            REQUIRE(g.getVertex(i).position.x <= UINT32_MAX);
        }
        for(int i = 0; i < vertCount; ++i) {
            REQUIRE(g.getVertex(i).position.y <= UINT32_MAX);
        }
}


std::size_t countEdges(Graph g) {
    std::size_t vertexCount = g.getVertexCount();
    std::unordered_set<std::size_t> unique {};

    for(std::size_t i = 0; i < vertexCount; ++i) {
        auto edges = g.getEdgesOfVertexIdx(i);
        for(auto edge: edges) {
            unique.insert(edge.identifier);
        }
    }
    return unique.size();
}

TEST_CASE( "Graph vertex and edge counts", "[graph counts]" ) {

    for(int i = 2; i < 100; ++i) {
        for(int x = 1; x < 10; ++x) {
            int vertCount = i;
            int edgeCount = x;
            float xMax = 10;
            float yMax = 10;

            auto g = Graph(edgeCount,vertCount,xMax,yMax);

            REQUIRE(g.getVertexCount() == vertCount);
            REQUIRE(countEdges(g) == edgeCount);
        }
    }

}
