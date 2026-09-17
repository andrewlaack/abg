#include "../include/utils.hpp"

#include <cassert>

float square(float x) { return x * x; }

double distanceSquared(Vector2 v1, Vector2 v2) {
    double xSquare = square(v1.x - v2.x);
    double ySquare = square(v1.y - v2.y);
    double result = xSquare + ySquare;
    assert(result >= 0);
    return result;
}
