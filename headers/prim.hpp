#pragma once

#include <cstdlib>
#include <unistd.h>
#include <raylib.h>
#include <queue>
#include "../headers/graph.hpp"
#include <unordered_set>

void explore(
        std::size_t cIdx, 
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>& toVisit,
        Edge& current,
        Graph& g
    );
void oneStepPrim(
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>& toVisit,
        std::unordered_set<std::size_t>& visitedIndices,
        Graph& g
    );
