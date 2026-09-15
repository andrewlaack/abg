#pragma once

#include <raylib.h>

#define DARKERGRAY   CLITERAL(Color){ 40, 40, 40, 255 }

float square(float x);
Vector2 randomPosition(float xMax, float yMax);
float distanceSquared(Vector2 v1, Vector2 v2);
