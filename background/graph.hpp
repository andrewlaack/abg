#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "edge.hpp"
#include "vertex.hpp"

class Graph {
    private:
        std::unordered_map<std::size_t, std::vector<Edge>> edges {};
        std::vector<Vertex> vertices {};
    public:
        // based on the edgeCount and vertCount, random edges and vertices will be created.
        Graph(std::size_t edgeCount, std::size_t vertCount, float xMax, float yMax);
        std::string toString();
        void render();
        void traverseVertexIdx(std::size_t idx);
        std::vector<Edge> getEdgesOfVertexIdx(std::size_t idx);
        void setEdgeTraversed(Edge e);
};
