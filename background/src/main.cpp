#include "../headers/graph.hpp"
#include "../headers/prim.hpp"
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

int main() {

    std::filesystem::create_directory("/dev/shm/bg");
    srand(clock());

    std::size_t edgeCount = 2000;
    std::size_t vertCount = 100;

    uint32_t xMax = 5120;
    uint32_t yMax = 1440;

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

        while (!WindowShouldClose() && toVisit.size() != 0) {
            sleep(10);
            BeginDrawing();
            ClearBackground(BLACK);
            g.render();
            EndDrawing(); 
            
            // Basically all of the cost happens within these bounds
            char path[] = "/dev/shm/bg/out.bmp";
            CustomTakeScreenshot(path);
            // TODO: Can this be done away with? It's not *that* slow...
            system("/usr/bin/feh --no-fehbg --bg-scale /dev/shm/bg/out.bmp");
            // Above here.

            oneStepPrim(toVisit, visitedIndices, g);

        }

    }

}
