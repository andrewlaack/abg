#include "utils.hpp"
#include <cstdlib>

float square(float x) {
    return x * x;
}

// call srand before invocation as this is a pure function.
Vector2 randomPosition(float xMax, float yMax) {
    float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * xMax;
    float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * yMax;
    Vector2 v {r1,r2};
    return v;
}

float distanceSquared(Vector2 v1, Vector2 v2) {
    float xSquare = square(v1.x - v2.x);
    float ySquare = square(v1.y - v2.y);
    return xSquare + ySquare;
}
