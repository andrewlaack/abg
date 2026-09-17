#include "../include/graph.hpp"

#include <raylib.h>

#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include "../include/constants.hpp"
#include "../include/utils.hpp"
#include "../include/vertex.hpp"

Graph::Graph(std::size_t edgeCount, std::size_t vertCount, uint32_t xMax,
             uint32_t yMax, std::uint32_t seed) {
    if (edgeCount > 0 && vertCount <= 1) {
        throw std::invalid_argument("This graph does not support self-loops.");
    }
    if (xMax <= 0 || yMax <= 0) {
        throw std::invalid_argument("xMax and yMax must be > 0.");
    }

    std::mt19937 rng{seed};
    std::uniform_int_distribution<std::size_t> pick1(0, vertCount - 1);

    std::uniform_int_distribution<std::uint32_t> pick2(0, xMax - 1);
    std::uniform_int_distribution<std::uint32_t> pick3(0, yMax - 1);

    vertices.reserve(vertCount);
    edges.resize(vertCount);

    for (std::size_t i = 0; i < vertCount; ++i) {
        Vector2 rnd = Vector2{(float)pick2(rng), (float)pick3(rng)};
        Vertex v{rnd, VERTEX_RENDER_SIZE};
        this->vertices.push_back(v);
    }
    for (std::size_t i = 0; i < edgeCount; ++i) {
        std::size_t idx1 = 0;
        std::size_t idx2 = 0;
        // no self-edges
        while (idx1 == idx2) {
            idx1 = pick1(rng);
            idx2 = pick1(rng);
        }

        double distance =
            distanceSquared(vertices[idx1].position, vertices[idx2].position);

        // this maintains the invariant that the first vertex of the edge is the
        // current one.
        Edge e1{idx1, idx2, distance, i};
        Edge e2{idx2, idx1, distance, i};
        this->edges[idx1].push_back(e1);
        this->edges[idx2].push_back(e2);
    }
}

std::string Graph::toString() noexcept {
    std::string result = "edges: {";

    for (auto edgesV : this->edges) {
        for (auto edge : edgesV) {
            result += edge.toString();
        }
    }

    result += "}";

    result += "\nvertices: {";

    for (auto vertex : this->vertices) {
        result += vertex.toString();
    }

    result += "}";
    return result;
}

// only render newly traversed edges / nodes.
void Graph::renderUnrenderedTraversed() noexcept {
    for (auto* edgesT : edgesToRender) {
        auto& edge = *edgesT;
        std::size_t idx1 = edge.v1Index;
        std::size_t idx2 = edge.v2Index;
        auto v1 = vertices[idx1].position;
        auto v2 = vertices[idx2].position;
        DrawLineEx(v1, v2, EDGE_REDNER_SIZE, WHITE);
    }
    edgesToRender = {};

    for (auto* vertex : verticesToRender) {
        vertex->render();
    }
    verticesToRender = {};
}

void Graph::render() noexcept {
    std::vector<Edge> visited{};
    for (auto& edgesT : this->edges) {
        for (auto& edge : edgesT) {
            if (edge.v1Index < edge.v2Index) {
                continue;  // since edges are tracked twice with v1
                           // it's safe to skip one of them.
            }
            std::size_t idx1 = edge.v1Index;
            std::size_t idx2 = edge.v2Index;
            auto v1 = vertices[idx1].position;
            auto v2 = vertices[idx2].position;
            if (edge.traversed) {
                visited.push_back(edge);
            } else {
                DrawLineEx(v1, v2, EDGE_REDNER_SIZE, DARKERGRAY);
            }
        }
    }

    for (auto& vertex : this->vertices) {
        vertex.render();
    }

    // ensure we draw visited over unvisited for better looks
    for (auto& edge : visited) {
        if (edge.v1Index < edge.v2Index) {
            continue;  // since edges are tracked twice with v1
                       // it's safe to skip one of them.
        }
        std::size_t idx1 = edge.v1Index;
        std::size_t idx2 = edge.v2Index;
        auto v1 = vertices[idx1].position;
        auto v2 = vertices[idx2].position;
        DrawLineEx(v1, v2, EDGE_REDNER_SIZE, WHITE);
    }
}

void Graph::traverseVertexIdx(std::size_t idx) {
    this->vertices[idx].visited = true;
    verticesToRender.push_back(&vertices[idx]);
}

// we assume the current vertex is already marked as traversed so we check to
// see if the other is here.
std::vector<Edge>* Graph::getEdgesWithUnvisitedVertices(std::size_t idx) {
    std::vector<Edge>* result = new std::vector<Edge>{};
    for (auto edge : edges[idx]) {
        if (!vertices[edge.v2Index].visited && !edge.traversed) {
            result->push_back(edge);
        }
    }
    return result;
}

std::vector<Edge> Graph::getEdgesOfVertexIdx(std::size_t idx) {
    return this->edges[idx];
}

void Graph::setEdgeTraversed(Edge e) {
    std::size_t source = e.v1Index;
    std::size_t destination = e.v2Index;

    if (source == destination) {
        return;
    }

    auto& cEdges = edges[source];

    for (auto& edge : cEdges) {
        if (edge.v2Index == destination || edge.v1Index == destination) {
            edge.traversed = true;
        }
    }

    auto& oEdges = edges[destination];

    for (auto& edge : oEdges) {
        if (edge.v2Index == source || edge.v1Index == source) {
            edge.traversed = true;
            edgesToRender.push_back(&edge);
        }
    }
}

Vertex Graph::getVertex(std::size_t idx) {
    // idx can't be negative bc size_t
    if (idx >= vertices.size()) {
        throw std::invalid_argument("idx out of bounds for vertex list");
    }
    return vertices[idx];
}

std::size_t Graph::getVertexCount() const noexcept { return vertices.size(); }
