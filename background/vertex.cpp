#include "vertex.hpp"
#include <string>
#include <raylib.h>

Vertex::Vertex(Vector2 position, float drawSize) 
    : position(position), drawSize(drawSize) {}


std::string Vertex::toString() {
    std::string result = "(" + std::to_string(this->position.x) + ", " + std::to_string(this->position.y) + ")";
    return result;
}


void Vertex::render() {
    if(visited) {
        DrawCircle(position.x, position.y, drawSize, WHITE);
    } else {
        DrawCircle(position.x, position.y, drawSize, DARKGRAY);
    }
}
