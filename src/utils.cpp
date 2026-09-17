#include "../include/utils.hpp"

#include <cassert>

float square(float x) { return x * x; }

float distanceSquared(Vector2 v1, Vector2 v2) {
    float xSquare = square(v1.x - v2.x);
    float ySquare = square(v1.y - v2.y);
    float result = xSquare + ySquare;
    return result;
}
