#include "raylib.h"
#include "edge.h"
#include <stdio.h>

#define VERTEX_SIZE 5

void draw_edges(Edge* edges, int length) {
    for(int i = 0; i < length; ++i) {
        Edge e = edges[i];

        Vertex v1 = *e.v1;
        Vertex v2 = *e.v2;
        
        // TODO: Convert this to a function.
        Vector2 v1_p;
        v1_p.x = v1.x;
        v1_p.y = v1.y;
        Vector2 v2_p;
        v2_p.x = (float)v2.x;
        v2_p.y = (float)v2.y;
        DrawLineEx(v1_p, v2_p, 1,DARKGRAY);
    }
}

void draw_vertices(Vertex* vertices, int length) {
    for(int i = 0; i < length; ++i) {
        Vertex v = vertices[i];
        DrawCircle(v.x,v.y,VERTEX_SIZE, WHITE);
    }
}

