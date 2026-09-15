#pragma once

#include <raylib.h>
#include <string>

class Vertex {
    public:
        Vertex(Vector2 position, float drawSize);
        Vector2 position;
        float drawSize;
        std::string toString();
        void render();
        bool visited = false;
};
