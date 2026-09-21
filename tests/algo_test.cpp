#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <iostream>
#include <random>

#include "../include/prim.hpp"

TEST_CASE("Small Prim algorithm", "[small prim algo]") {
    std::size_t edgeCount = 1;
    std::size_t vertCount = 2;

    float xMax = 5120;
    float yMax = 1440;

    Graph g = Graph(edgeCount, vertCount, xMax, yMax);
    std::unordered_set<std::size_t> visitedIndices{};
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> toVisit{};
    std::vector<Edge> edges = g.getEdgesOfVertexIdx(0);
    std::vector<double> minEdgeToVertex(vertCount, -1);

    for (auto edge : edges) {
        toVisit.push(edge);
    }

    g.traverseVertexIdx(0);
    visitedIndices.insert(0);

    while (toVisit.size() != 0) {
        oneStepPrim(toVisit, visitedIndices, g, minEdgeToVertex);
    }
    // this will be true bc 2 vertices 1 edge...
    // our graph may have multi-edges.
    REQUIRE(visitedIndices.size() == 2);
}

bool isConnected(Graph g) {
    std::unordered_set<std::size_t> verticesFound{0};

    std::vector<std::size_t> current{};

    while (true) {
        for (auto key : verticesFound) {
            auto edges = g.getEdgesOfVertexIdx(key);
            for (auto edge : edges) {
                current.push_back(edge.v1Index);
                current.push_back(edge.v2Index);
            }
        }
        std::size_t len = verticesFound.size();
        for (auto idx : current) {
            verticesFound.insert(idx);
        }
        if (len == verticesFound.size()) {
            break;
        }
    }

    return verticesFound.size() == g.getVertexCount();
}

TEST_CASE("Large Prim algorithm", "[Large prim algo]") {
    std::size_t edgeCount = 3000;
    std::size_t vertCount = 1000;

    float xMax = 5120;
    float yMax = 1440;

    Graph g = Graph(edgeCount, vertCount, xMax, yMax);
    std::unordered_set<std::size_t> visitedIndices{};
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> toVisit{};
    std::vector<double> minEdgeToVertex(vertCount, -1);

    do {
        g = Graph(edgeCount, vertCount, xMax, yMax);
    } while (!isConnected(g));

    g.traverseVertexIdx(0);
    visitedIndices.insert(0);

    std::vector<Edge> edges = g.getEdgesOfVertexIdx(0);

    for (auto edge : edges) {
        toVisit.push(edge);
    }

    while (toVisit.size() != 0) {
        oneStepPrim(toVisit, visitedIndices, g, minEdgeToVertex);
    }

    REQUIRE(visitedIndices.size() == vertCount);
}

TEST_CASE("Medium Prim algorithm", "[Medium prim algo]") {
    std::size_t edgeCount = 70;
    std::size_t vertCount = 51;

    float xMax = 5120;
    float yMax = 1440;

    Graph g = Graph(edgeCount, vertCount, xMax, yMax);
    std::unordered_set<std::size_t> visitedIndices{};
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> toVisit{};
    std::vector<double> minEdgeToVertex(vertCount, -1);

    do {
        g = Graph(edgeCount, vertCount, xMax, yMax);
    } while (!isConnected(g));

    g.traverseVertexIdx(0);
    visitedIndices.insert(0);

    std::vector<Edge> edges = g.getEdgesOfVertexIdx(0);

    for (auto edge : edges) {
        toVisit.push(edge);
    }

    while (toVisit.size() != 0) {
        oneStepPrim(toVisit, visitedIndices, g, minEdgeToVertex);
    }

    REQUIRE(visitedIndices.size() == vertCount);
}

TEST_CASE("Staircase Prim algorithm", "[Staircase prim algo]") {
    for (int i = 2; i < 30; ++i) {
        for (int x = i - 1; x < 60; ++x) {
            std::size_t edgeCount = x;
            std::size_t vertCount = i;

            float xMax = 5120;
            float yMax = 1440;

            std::vector<double> minEdgeToVertex(vertCount, -1);
            Graph g = Graph(edgeCount, vertCount, xMax, yMax);
            std::unordered_set<std::size_t> visitedIndices{};
            std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>
                toVisit{};

            do {
                g = Graph(edgeCount, vertCount, xMax, yMax);
            } while (!isConnected(g));

            std::vector<Edge> edges = g.getEdgesOfVertexIdx(0);
            for (auto edge : edges) {
                toVisit.push(edge);
            }
            g.traverseVertexIdx(0);
            visitedIndices.insert(0);

            while (toVisit.size() != 0) {
                oneStepPrim(toVisit, visitedIndices, g, minEdgeToVertex);
            }

            REQUIRE(visitedIndices.size() == vertCount);
        }
    }
}

TEST_CASE("Small Prim Test", "[Small full validation]") {
    for (int i = 0; i < 100; ++i) {
        std::size_t edgeCount = 10;
        std::size_t vertCount = 5;

        float xMax = 5120;
        float yMax = 1440;

        Graph g = Graph(edgeCount, vertCount, xMax, yMax);
        do {
            g = Graph(edgeCount, vertCount, xMax, yMax);
        } while (!isConnected(g));

        std::unordered_set<std::size_t> visitedIndices{};
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>
            toVisit{};

        for (auto edge : g.getEdgesOfVertexIdx(0)) toVisit.push(edge);
        g.traverseVertexIdx(0);
        visitedIndices.insert(0);

        std::unordered_set<std::size_t> vBefore = visitedIndices;

        bool havePrior = false;
        Edge prior = toVisit.top();
        std::unordered_set<std::size_t> visibleAtPrior;
        std::vector<double> minEdgeToVertex(vertCount, -1);

        while (toVisit.size() != 0) {
            auto current = toVisit.top();
            if (havePrior) {
                bool wasPresent = visibleAtPrior.count(current.v1Index) > 0 ||
                                  visibleAtPrior.count(current.v2Index) > 0;
                // anytime we use the same source node two steps in a row, the
                // second weight must be smaller.
                if (wasPresent) {
                    REQUIRE(current.length2 >= prior.length2);
                }
            }

            prior = current;
            visibleAtPrior = visitedIndices;
            havePrior = true;
            oneStepPrim(toVisit, visitedIndices, g, minEdgeToVertex);
            bool valid = vBefore.size() + 1 == visitedIndices.size() ||
                         vBefore.size() == vertCount;
            REQUIRE(valid);
            vBefore = visitedIndices;
        }
        REQUIRE(visitedIndices.size() == vertCount);
    }
}

// traverse the graph randomly, ensuring we visit all vertices then return edge
// weight sum. This ensures our admissible heuristic always beats or is on par
// with an inadmissible one (this one).

double randomTraversalCost(Graph g) {
    std::uint32_t seed = std::random_device{}();
    std::mt19937 rng{seed};

    std::size_t count = g.getVertexCount();
    std::uniform_int_distribution<std::size_t> pick1(0, count - 1);

    std::size_t traversed = 0;
    double cost = 0;

    g.traverseVertexIdx(pick1(rng));  // start
    traversed += 1;

    while (traversed < g.getVertexCount()) {
        std::size_t idx = pick1(rng);
        if (g.getVertex(idx).visited) {
            std::vector<Edge> edges = g.getEdgesOfVertexIdx(idx);
            std::uniform_int_distribution<std::size_t> pick2(0,
                                                             edges.size() - 1);
            std::size_t selection = pick2(rng);
            if (!g.getVertex(edges[selection].v2Index).visited) {
                cost += edges[selection].length2;
                g.setEdgeTraversed(edges[selection]);
                g.traverseVertexIdx(edges[selection].v2Index);
                traversed += 1;
            }
        }
    }
    return cost;
}

TEST_CASE("Prim Correctness Test", "[Correctness test for MST]") {
    for (int i = 0; i < 100; ++i) {
        std::size_t edgeCount = 10;
        std::size_t vertCount = 5;

        float xMax = 5120;
        float yMax = 1440;

        Graph g = Graph(edgeCount, vertCount, xMax, yMax);
        do {
            g = Graph(edgeCount, vertCount, xMax, yMax);
        } while (!isConnected(g));  // this passes by value

        double rndCost = randomTraversalCost(g);  // this passes by value

        std::unordered_set<std::size_t> visitedIndices{};
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>
            toVisit{};

        for (auto edge : g.getEdgesOfVertexIdx(0)) toVisit.push(edge);
        g.traverseVertexIdx(0);
        visitedIndices.insert(0);

        std::unordered_set<std::size_t> vBefore = visitedIndices;

        bool havePrior = false;
        Edge prior = toVisit.top();
        std::unordered_set<std::size_t> visibleAtPrior;
        std::vector<double> minEdgeToVertex(vertCount, -1);

        double primCost = 0;

        while (toVisit.size() != 0) {
            auto current = toVisit.top();
            if (havePrior) {
                bool wasPresent = visibleAtPrior.count(current.v1Index) > 0 ||
                                  visibleAtPrior.count(current.v2Index) > 0;
                // anytime we use the same source node two steps in a row, the
                // second weight must be smaller.
                if (wasPresent) {
                    REQUIRE(current.length2 >= prior.length2);
                }
            }

            prior = current;
            visibleAtPrior = visitedIndices;
            havePrior = true;

            primCost +=
                oneStepPrim(toVisit, visitedIndices, g, minEdgeToVertex);
            bool valid = vBefore.size() + 1 == visitedIndices.size() ||
                         vBefore.size() == vertCount;
            REQUIRE(valid);
            vBefore = visitedIndices;
        }
        REQUIRE(visitedIndices.size() == vertCount);
        REQUIRE(primCost <= rndCost);
    }
}
