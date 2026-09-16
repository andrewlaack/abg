#include "../headers/edge.hpp"
#include <cstddef>

Edge::Edge(std::size_t v1, std::size_t v2, double length2, std::size_t identifier)
    : v1Index(v1), v2Index(v2), length2(length2), identifier(identifier) {}

std::string Edge::toString() const noexcept {
    return "(" + std::to_string(this->v1Index) + ", " + std::to_string(this->v2Index) + ")";
}

bool Edge::operator<(const Edge& other) const {
    return length2 < other.length2;
}

bool Edge::operator>(const Edge& other) const {
    return length2 > other.length2;
}
