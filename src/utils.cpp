#include "../include/utils.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>

float square(float x) { return x * x; }

// call srand before invocation as this is a pure function.
Vector2 randomPosition(uint32_t xMax, uint32_t yMax) {
    uint32_t r1 = rand() % xMax;
    uint32_t r2 = rand() % yMax;
    Vector2 v{(float)r1, (float)r2};
    return v;
}

float distanceSquared(Vector2 v1, Vector2 v2) {
    float xSquare = square(v1.x - v2.x);
    float ySquare = square(v1.y - v2.y);
    float result = xSquare + ySquare;
    assert(result >= 0);
    return result;
}
