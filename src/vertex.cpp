#include "../include/vertex.hpp"
#include <raylib.h>
#include <string>

Vertex::Vertex(Vector2 position, float drawSize)
    : position(position), drawSize(drawSize) {}

std::string Vertex::toString() {
  std::string result = "(x: " + std::to_string(this->position.x) +
                       ", y: " + std::to_string(this->position.y) +
                       ", visited: " + std::to_string(this->visited) + ")";
  return result;
}

void Vertex::render() {
  if (visited) {
    DrawCircle(position.x, position.y, drawSize, WHITE);
  } else {
    DrawCircle(position.x, position.y, drawSize, DARKGRAY);
  }
}
