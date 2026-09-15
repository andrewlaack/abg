#include "vert.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Vertex gen_vertex() {
    int y = rand() % 1440;
    int x = rand() % 5120;
    Vertex v;
    v.x = x;
    v.y = y;
    return v;
}

void print_vertex(Vertex* v) {
    printf("x: %i, y: %i", v->x, v->y);
}

Vertex* gen_vertices(int vtCount) {
    Vertex* vertices = (Vertex*)malloc(sizeof(Vertex) * vtCount);
    for(int i = 0; i < vtCount; ++i) {
        Vertex v = gen_vertex();
        vertices[i] = v;
    }
    return vertices;

}

float vert_dist(Vertex* v1, Vertex* v2) {
    float dx = (float)v1->x - (float)v2->x;
    float dy = (float)v1->y - (float)v2->y;
    return sqrt(dx*dx + dy*dy);
}
