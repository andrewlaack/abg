#include "../include/edge.hpp"
#include <cstddef>
#include <string>

Edge::Edge(std::size_t v1, std::size_t v2, double length2,
           std::size_t identifier)
    : v1Index(v1), v2Index(v2), length2(length2), identifier(identifier) {}

std::string Edge::toString() const noexcept {
  return "(v1: " + std::to_string(this->v1Index) +
         ", v2: " + std::to_string(this->v2Index) +
         +", traversed: " + std::to_string(this->traversed) + ")";
}

bool Edge::operator<(const Edge &other) const {
  return length2 < other.length2;
}

bool Edge::operator>(const Edge &other) const {
  return length2 > other.length2;
}
