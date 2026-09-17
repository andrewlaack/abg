#pragma once

#include "edge.hpp"
#include "vertex.hpp"
#include <cstddef>
#include <cstdint>
#include <random>
#include <string>
#include <vector>

class Graph {
private:
    std::vector<std::vector<Edge>> edges{};
    std::vector<Vertex> vertices {};
    std::vector<Vertex*> verticesToRender {}; // these point to 
    std::vector<Edge*> edgesToRender {};      // elements in the other vectors.
                                             // past init, vertices and edges don't vary

public:
  // based on the edgeCount and vertCount, random edges and vertices will be
  // created.
  Graph(std::size_t edgeCount, std::size_t vertCount, uint32_t xMax,
        uint32_t yMax, std::uint32_t seed = std::random_device{}());
  std::string toString() noexcept;
  void render() noexcept;
  void renderUnrenderedTraversed() noexcept;
  void traverseVertexIdx(std::size_t idx);
  std::vector<Edge> getEdgesOfVertexIdx(std::size_t idx);
  std::vector<Edge>* getEdgesWithUnvisitedVertices(std::size_t idx);
  void setEdgeTraversed(Edge e);
  Vertex getVertex(std::size_t idx);
  std::size_t getVertexCount() const noexcept;
};
