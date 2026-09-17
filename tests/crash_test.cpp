#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdint>
#include <random>
#include <thread>
#include <vector>

#include "../include/prim.hpp"

void run(size_t mv, size_t me, uint32_t iterations) {
    uint32_t seed = std::random_device{}();
    std::mt19937 rng{seed};

    size_t vMax = mv;
    size_t eMax = me;

    size_t xMax = 60000;
    size_t yMax = 60000;

    std::uniform_int_distribution<std::size_t> pick1(2, vMax - 1);
    std::uniform_int_distribution<std::size_t> pick2(0, eMax - 1);

    std::uniform_int_distribution<uint> pick3(1, xMax - 1);
    std::uniform_int_distribution<uint> pick4(1, yMax - 1);

    for (uint32_t i = 0; i < iterations; ++i) {
        std::size_t vertCount = pick1(rng);
        std::size_t edgeCount = pick2(rng);

        uint32_t xSel = pick3(rng);
        uint32_t ySel = pick4(rng);

        Graph g = Graph(edgeCount, vertCount, xSel, ySel);
        std::unordered_set<std::size_t> visitedIndices{};
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>
            toVisit{};
        std::vector<double> minEdgeToVertex(vertCount, -1);

        g.traverseVertexIdx(0);
        visitedIndices.insert(0);

        std::vector<Edge> edges = g.getEdgesOfVertexIdx(0);

        for (auto edge : edges) {
            toVisit.push(edge);
        }

        while (toVisit.size() != 0) {
            oneStepPrim(toVisit, visitedIndices, g, minEdgeToVertex);
        }
        REQUIRE(true);  // just fuzzing for this one.
    }
}

void runs() { run(100, 500, 10000); }
void runl() { run(100000, 1000000, 100); }

TEST_CASE("Small prim algorithm not guaranteed connected", "[Small prim]") {
    std::vector<std::thread*> threads{};

    for (int i = 0; i < 10; ++i) {
        std::thread* t1 = new std::thread{runs};
        threads.push_back(t1);
    }
    for (int i = 0; i < 10; ++i) {
        threads[i]->join();
        delete threads[i];
    }
}

TEST_CASE("Large prim algorithm not guaranteed connected", "[Large prim]") {
    std::vector<std::thread*> threads{};
    for (int i = 0; i < 10; ++i) {
        std::thread* t1 = new std::thread{runl};
        threads.push_back(t1);
    }
    for (int i = 0; i < 10; ++i) {
        threads[i]->join();
        delete threads[i];
    }
}
