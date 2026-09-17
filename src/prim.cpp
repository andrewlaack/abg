#include "../include/prim.hpp"

#include <raylib.h>
#include <unistd.h>

#include <cstdlib>
#include <queue>
#include <unordered_set>

#include "../include/graph.hpp"

void explore(
    std::size_t cIdx,
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>& toVisit,
    Edge& current, Graph& g, std::unordered_set<std::size_t>& visitedIndices) {
    visitedIndices.insert(cIdx);
    g.traverseVertexIdx(cIdx);
    g.setEdgeTraversed(
        current);  // this must happen before the next line below.
    std::vector<Edge>* edges = g.getEdgesWithUnvisitedVertices(
        cIdx);  // this gets edges with two unvisited vertices connected to
                // cIdx.
    for (auto& edge : *edges) {
        toVisit.push(std::move(edge));
    }
    delete edges;
}

void oneStepPrim(
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>& toVisit,
    std::unordered_set<std::size_t>& visitedIndices, Graph& g) {
    bool found = false;

    if (toVisit.size() == 0) {
        return;
    }
    while (found == false) {
        if (toVisit.size() == 0) {
            return;
        }

        found = true;
        auto current = toVisit.top();
        toVisit.pop();

        if (visitedIndices.find(current.v2Index) == visitedIndices.end()) {
            auto cIdx = current.v2Index;
            explore(cIdx, toVisit, current, g, visitedIndices);

        } else if (visitedIndices.find(current.v1Index) ==
                   visitedIndices.end()) {
            auto cIdx = current.v1Index;
            explore(cIdx, toVisit, current, g, visitedIndices);
        } else {
            found = false;
        }
    }
}
