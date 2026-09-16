#include "../include/graph.hpp"
#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include "snapshot_shared.cpp"

std::string readFileToString(std::string filename) {
        auto in = std::ifstream ("tests/snapshot/" + filename + ".out");
        std::ostringstream sstr;
        sstr << in.rdbuf();
        return sstr.str();
}


TEST_CASE( "Basic graph serialization snapshot", "[basic graph serialization snapshot]" ) {
    Graph g = basicGraphSerialization();
    REQUIRE(readFileToString("basicGraph") == g.toString());
}

TEST_CASE( "Traversed graph serialization snapshot", "[traversed graph serialization snapshot]" ) {
    Graph g = fullTraversalSerialization();
}
