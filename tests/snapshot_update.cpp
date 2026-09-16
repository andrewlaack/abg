#include "../include/graph.hpp"
#include "../include/prim.hpp"
#include <fstream>
#include <filesystem>
#include <queue>
#include <unordered_set>


void snapshotGraph(std::string testName, Graph g) {

    std::filesystem::path path{ "tests/snapshot" };
    path /= testName + ".out";
    std::filesystem::create_directories(path.parent_path());
    std::ofstream ofs(path);
    ofs << g.toString();

}

void updateBasicGraphSerialization() {
    srand(42);
    int vertCount = 10;
    int edgeCount = 10;
    float xMax = 10;
    float yMax = 10;
    auto g = Graph(edgeCount,vertCount,xMax,yMax);
    snapshotGraph("basicGraph",g);
}


void updateFullTraversalSerialization() {
    srand(42);
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
    
    snapshotGraph("traversedGraph",g);
}

int main() {
    updateBasicGraphSerialization();
    updateFullTraversalSerialization();
}
