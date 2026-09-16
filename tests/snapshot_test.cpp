#include "../include/graph.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE( "Basic graph serialization snapshot", "[basic graph serialization snapshot]" ) {
    srand(42);
    int vertCount = 10;
    int edgeCount = 10;
    float xMax = 10;
    float yMax = 10;
    auto g = Graph(edgeCount,vertCount,xMax,yMax);
    std::cout << g.toString() << std::endl;
}
