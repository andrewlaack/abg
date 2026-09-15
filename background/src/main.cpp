#include "../headers/graph.hpp"
#include <cstdlib>
#include <unistd.h>
#include <raylib.h>
#include <ctime>
#include <queue>
#include <unordered_set>
#include <filesystem>

void CustomTakeScreenshot(char* filePath){
    const char *customParam;
    Image screenshot = LoadImageFromScreen(); 
    ExportImage(screenshot, TextFormat(filePath, customParam));
    UnloadImage(screenshot); 
}
void explore(
        std::size_t cIdx, 
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>& toVisit,
        Edge& current,
        Graph& g
    ) {
    g.traverseVertexIdx(cIdx);
    std::vector<Edge> edges = g.getEdgesOfVertexIdx(cIdx);
    for(auto edge: edges) {
        toVisit.push(edge);
    }
    g.setEdgeTraversed(current);
}

int main() {

    std::filesystem::create_directory("/dev/shm/bg");
    srand(clock());

    std::size_t edgeCount = 30;
    std::size_t vertCount = 10;

    float xMax = 5120;
    float yMax = 1440;

    SetConfigFlags(FLAG_WINDOW_HIDDEN);
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
            sleep(5);

            BeginDrawing();
            ClearBackground(BLACK);
            g.render();
            EndDrawing(); 
            
            char path[] = "/dev/shm/bg/out.png";
            CustomTakeScreenshot(path);
            // TODO: Can this be done away with? It's not *that* slow...
            system("/usr/bin/feh --no-fehbg --bg-tile /dev/shm/bg/out.png");


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
                    explore(cIdx, toVisit, current, g);

                } else if(visitedIndices.find(current.v1Index) == visitedIndices.end()) {
                    auto cIdx = current.v1Index;
                    visitedIndices.insert(current.v1Index);
                    explore(cIdx, toVisit, current, g);
                } else {
                    found = false;
                }

            }

        }

    }

}
