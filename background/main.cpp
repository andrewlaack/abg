#include "graph.hpp"
#include <unistd.h>
#include <raylib.h>
#include <ctime>
#include <queue>
#include <unordered_set>

int main() {
    srand(clock());

    std::size_t edgeCount = 2000;
    std::size_t vertCount = 200;

    float xMax = 5120;
    float yMax = 1440;
    

    InitWindow(xMax, yMax, "Raylib animation window");

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

        while (!WindowShouldClose()) {
            sleep(1);

            BeginDrawing();
            ClearBackground(BLACK);
            g.render();
            EndDrawing(); 

            bool found = false;
            if(toVisit.size() == 0) {
                break;
            }
            while(found == false) {
                if(toVisit.size() == 0) {
                    break;
                }

                found = true;
                auto current = toVisit.top();
                toVisit.pop();

                if(visitedIndices.find(current.v2Index) == visitedIndices.end()) {
                    auto cIdx = current.v2Index;
                    visitedIndices.insert(current.v2Index);
                    g.traverseVertexIdx(cIdx);
                    // TODO: Make this a function.
                    std::vector<Edge> edges = g.getEdgesOfVertexIdx(cIdx);
                    for(auto edge: edges) {
                        toVisit.push(edge);
                    }
                g.setEdgeTraversed(current);

                } else if(visitedIndices.find(current.v1Index) == visitedIndices.end()) {
                    auto cIdx = current.v1Index;
                    visitedIndices.insert(current.v1Index);
                    g.traverseVertexIdx(cIdx);
                    // TODO: Make this a function.
                    std::vector<Edge> edges = g.getEdgesOfVertexIdx(cIdx);
                    for(auto edge: edges) {
                        toVisit.push(edge);
                    }
                    g.setEdgeTraversed(current);
                } else {
                    found = false;
                }

            }

    }

    }

}
