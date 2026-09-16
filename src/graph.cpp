#include "../headers/graph.hpp"
#include "../headers/constants.hpp"
#include "../headers/vertex.hpp"
#include "../headers/utils.hpp"
#include <cstddef>
#include <cstdint>
#include <raylib.h>
#include <stdexcept>

Graph::Graph(std::size_t edgeCount, std::size_t vertCount, uint32_t xMax, uint32_t yMax) {

    if(edgeCount > 0 && vertCount <= 1) {
        throw std::invalid_argument("This graph does not support self-loops.");
    }
    if(xMax <= 0 || yMax <= 0) {
        throw std::invalid_argument("xMax and yMax must be > 0.");
    }


    for(std::size_t i = 0; i < vertCount; ++i) {
        Vector2 rnd = randomPosition(xMax, yMax);
        Vertex v {rnd,VERTEX_RENDER_SIZE};
        this->vertices.push_back(v);
    }
    for(std::size_t i = 0; i < edgeCount; ++i) {
        std::size_t idx1 = 0;
        std::size_t idx2 = 0;
        // no self-edges
        while (idx1 == idx2) {
            idx1 = std::rand() % vertCount;
            idx2 = std::rand() % vertCount;
        }
        
        Edge e {idx1, idx2, distanceSquared(vertices[idx1].position, vertices[idx2].position), i};
        this->edges[idx1].push_back(e);
        this->edges[idx2].push_back(e);
    }
}

std::string Graph::toString() noexcept {

    std::string result = "edges: {";

    for(auto pair: this->edges) {
        auto key = pair.first;
        for(auto edge: edges[key]) {
            result += edge.toString();
        }
    }
    
    result += "}";

    result += "\nvertices: {";

    for(auto vertex: this->vertices) {
        result += vertex.toString();
    }

    result += "}";
    return result;
}


void Graph::render() noexcept {
    
    // yes, this will double draw because we track 0 -> 1 and 1 -> 0
    
    std::vector<Edge> visited {};
    for(auto pair: this->edges) {
        auto edges = this->edges[pair.first];
        for(auto edge: edges) {
            std::size_t idx1 = edge.v1Index;
            std::size_t idx2 = edge.v2Index;
            auto v1 = vertices[idx1].position;
            auto v2 = vertices[idx2].position;
            if(edge.traversed) {
                visited.push_back(edge);
            } else {
                DrawLineEx(v1, v2, EDGE_REDNER_SIZE,DARKERGRAY);
            }
        }
    }
    
    for(auto vertex: this->vertices) {
        vertex.render();
    }

    // ensure we draw visited over unvisited for better looks
    for(auto edge: visited) {
        std::size_t idx1 = edge.v1Index;
        std::size_t idx2 = edge.v2Index;
        auto v1 = vertices[idx1].position;
        auto v2 = vertices[idx2].position;
        DrawLineEx(v1, v2, EDGE_REDNER_SIZE, WHITE);
    }
}

void Graph::traverseVertexIdx(std::size_t idx) {
    this->vertices[idx].visited = true;
}

std::vector<Edge> Graph::getEdgesOfVertexIdx(std::size_t idx) {
    return this->edges[idx];
}

void Graph::setEdgeTraversed(Edge e) {

    std::size_t source = e.v1Index;
    std::size_t destination = e.v2Index;

    if(source == destination) { 
        return;
    }

    auto& cEdges = edges[source];

    for(auto& edge : cEdges) {
        if(edge.v2Index == destination || edge.v1Index == destination) {
            edge.traversed = true;
        }
    }

    auto& oEdges = edges[destination];

    for(auto& edge : oEdges) {
        if(edge.v2Index == source || edge.v1Index == source) {
            edge.traversed = true;
        }
    }

}

Vertex Graph::getVertex(std::size_t idx) {
    // idx can't be negative bc size_t
    if(idx >= vertices.size()) {
        throw std::invalid_argument("idx out of bounds for vertex list");
    }
    return vertices[idx];
}


std::size_t Graph::getVertexCount() const noexcept {
    return vertices.size();
}
