#pragma once

#include <string>

class Edge {
public:
  // indices of v1 and v2
  Edge(std::size_t v1, std::size_t v2, double length2, std::size_t identifier);
  std::size_t v1Index;
  std::size_t v2Index;
  double length2;
  std::size_t identifier;
  bool traversed = false;
  std::string toString() const noexcept;
  bool operator<(const Edge &other) const;
  bool operator>(const Edge &other) const;
};
