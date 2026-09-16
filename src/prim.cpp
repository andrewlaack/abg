#include "../include/prim.hpp"
#include "../include/graph.hpp"
#include <cstdlib>
#include <queue>
#include <raylib.h>
#include <unistd.h>
#include <unordered_set>

void explore(
    std::size_t cIdx,
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> &toVisit,
    Edge &current, Graph &g, std::unordered_set<std::size_t> &visitedIndices) {

  visitedIndices.insert(cIdx);
  g.traverseVertexIdx(cIdx);

  g.setEdgeTraversed(current);

  std::vector<Edge> edges = g.getEdgesOfVertexIdx(cIdx);
  for (auto edge : edges) {
    toVisit.push(edge);
  }
}

void oneStepPrim(
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> &toVisit,
    std::unordered_set<std::size_t> &visitedIndices, Graph &g) {
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

    } else if (visitedIndices.find(current.v1Index) == visitedIndices.end()) {
      auto cIdx = current.v1Index;
      explore(cIdx, toVisit, current, g, visitedIndices);
    } else {
      found = false;
    }
  }
}
