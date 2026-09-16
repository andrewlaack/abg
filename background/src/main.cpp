#include "../headers/graph.hpp"
#include "../headers/prim.hpp"
#include "../headers/background.hpp"
#include "../headers/constants.hpp"
#include "../vendor/argparse.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <raylib.h>
#include <ctime>
#include <queue>
#include <unordered_set>

int main(int argc, char** argv) {

    srand(clock());
    // reverse semver
    argparse::ArgumentParser program("abg", "10.0.0");

    program.add_argument("--vertices")
        .help("number of vertices in the graph")
        .default_value(DEFAULT_VERTEX_COUNT)
        .scan<'i', std::size_t>();

    program.add_argument("--sleep", "-s")
        .help("amount of time to sleep between traversals")
        .default_value(DEFAULT_SLEEP_TIME)
        .scan<'g', float>();


    program.add_argument("--edges", "-e")
        .help("number of edges in the graph")
        .default_value(DEFAULT_EDGE_COUNT)
        .scan<'i', std::size_t>();

    try {
      program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
      std::cerr << err.what() << std::endl;
      std::cerr << program;
      std::exit(1);
    }

    std::size_t vertexCount = program.get<std::size_t>("--vertices");
    std::size_t edgeCount = program.get<std::size_t>("--edges");
    float sleepTime = program.get<float>("--sleep");

    SetTraceLogLevel(LOG_ERROR);

    auto ss = getScreenSize();

    uint32_t xMax = ss[0];
    uint32_t yMax = ss[1];

    // would be nice to do this all in background.cpp, but raylib and x11 can't both be imported 
    // by the same file because of some dependency chain thing with Font.

    InitWindow(xMax, yMax, "abg");
    sendToBg("abg");

    int count = 0;
    while (!WindowShouldClose()) {
        count += 1;

        Graph g = Graph(edgeCount, vertexCount, xMax,yMax);
        std::unordered_set<std::size_t> visitedIndices {};
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> toVisit {};
        std::vector<Edge> edges = g.getEdgesOfVertexIdx(0);
        for(auto edge: edges) {
            toVisit.push(edge);
        }
        g.traverseVertexIdx(0);
        visitedIndices.insert(0);

        while (!WindowShouldClose() && toVisit.size() != 0) {
            BeginDrawing();
            ClearBackground(BLACK);
            g.render();
            EndDrawing(); 
            usleep((int)(sleepTime * 1000000));
            oneStepPrim(toVisit, visitedIndices, g);
        }
    }
}
