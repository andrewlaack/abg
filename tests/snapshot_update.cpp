#include "../include/graph.hpp"
#include "snapshot_shared.cpp"
#include <fstream>
#include <filesystem>

void snapshotGraph(std::string testName, Graph g) {
    std::filesystem::path path{ "tests/snapshot" };
    path /= testName + ".out";
    std::filesystem::create_directories(path.parent_path());
    std::ofstream ofs(path);
    ofs << g.toString();

}

int main() {
    Graph g1 = basicGraphSerialization();
    snapshotGraph("basicGraph", g1);
    Graph g2 = fullTraversalSerialization();
    snapshotGraph("traversedGraph", g2);
    Graph g3 = fullTraversalLargerSerialization();
    snapshotGraph("traversedLargerGraph", g3);

}
