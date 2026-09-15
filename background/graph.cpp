#include "graph.hpp"
#include "vertex.hpp"
#include "utils.hpp"
#include <cstddef>
#include <raylib.h>
#include <iostream>

Graph::Graph(std::size_t edgeCount, std::size_t vertCount, float xMax, float yMax) {
    for(std::size_t i = 0; i < vertCount; ++i) {
        Vector2 rnd = randomPosition(xMax, yMax);
        Vertex v {rnd,5};
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
        
        Edge e {idx1, idx2, distanceSquared(vertices[idx1].position, vertices[idx2].position)};
        this->edges[idx1].push_back(e);
        this->edges[idx2].push_back(e);
    }
}

std::string Graph::toString() {

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


void Graph::render() {
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
                DrawLineEx(v1, v2, 1,DARKERGRAY);
            }
        }
    }

    // ensure we draw visited over unvisited for better looks
    for(auto edge: visited) {
        std::size_t idx1 = edge.v1Index;
        std::size_t idx2 = edge.v2Index;
        auto v1 = vertices[idx1].position;
        auto v2 = vertices[idx2].position;
        DrawLineEx(v1, v2, 1, WHITE);
    }

    for(auto vertex: this->vertices) {
        vertex.render();
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
