#pragma once

#include <cstddef>
#include <string>

class Edge {
    public:
        // indices of v1 and v2
        Edge(std::size_t v1, std::size_t v2, float length2);
        std::size_t v1Index;
        std::size_t v2Index;
        float length2;
        bool traversed = false;
        std::string toString();
        bool operator<(const Edge& other) const;
        bool operator>(const Edge& other) const;
};
