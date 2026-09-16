#include "../headers/graph.hpp"
#include "../headers/prim.hpp"
#include "../headers/background.hpp"
#include <cstdlib>
#include <unistd.h>
#include <raylib.h>
#include <ctime>
#include <queue>
#include <unordered_set>

int main() {

    SetTraceLogLevel(LOG_ERROR);
    srand(clock());

    std::size_t edgeCount = 500;
    std::size_t vertCount = 100;

    auto ss = getScreenSize();

    uint32_t xMax = ss[0];
    uint32_t yMax = ss[1];

    // would be nice to do this all in background.cpp, but raylib and x11 can't both be imported 
    // by the same file because of some dependency chain thing with Font.

    InitWindow(xMax, yMax, "background-ray");
    sendToBg("background-ray");

    while (!WindowShouldClose()) {

        Graph g = Graph(edgeCount, vertCount, xMax,yMax);
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
            sleep(5);
            oneStepPrim(toVisit, visitedIndices, g);

        }

    }

}
