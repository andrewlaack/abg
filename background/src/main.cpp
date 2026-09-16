#include "../headers/graph.hpp"
#include "../headers/prim.hpp"
#include "../headers/background.hpp"
#include "../headers/constants.hpp"
#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <raylib.h>
#include <ctime>
#include <queue>
#include <unordered_set>

int main() {

    SetTraceLogLevel(LOG_ERROR);
    srand(clock());


    auto ss = getScreenSize();

    uint32_t xMax = ss[0];
    uint32_t yMax = ss[1];

    // would be nice to do this all in background.cpp, but raylib and x11 can't both be imported 
    // by the same file because of some dependency chain thing with Font.

    InitWindow(xMax, yMax, "background-ray");
    sendToBg("background-ray");

    while (!WindowShouldClose()) {

        // TODO: What should the cli include? Edges and vertices perhaps?
        // I'd also like other graph algos in here too so perhaps --vertices --edges and {algorithm}?
        // would also like to have nearest neighbor travelling salesman too

        Graph g = Graph(DEFAULT_EDGE_COUNT, DEFAULT_VERTEX_COUNT, xMax,yMax);
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
            sleep(1);
            oneStepPrim(toVisit, visitedIndices, g);

        }

    }

}
