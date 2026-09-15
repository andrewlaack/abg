#include "edge.hpp"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

void print_edge(Edge *e) {
    printf("v1.x = %i, v1.y = %i\nv2.x = %i, v2.y = %i", e->v1->x, e->v1->y, e->v2->x, e->v2->y);
}

Edge gen_edge(int idx1, int idx2, Vertex* vertices) {
    Edge e;
    e.v1 = &vertices[idx1];
    e.v2 = &vertices[idx2];
    e.weight = vert_dist(e.v1, e.v2);
    return e;
}

Edge* gen_edges(Vertex* vertices, int vtCount, int edgeCount) {
    Edge* edges = (Edge*)malloc(sizeof(Edge) * edgeCount);
    for(int i = 0; i < edgeCount; ++i) {
        int idx1 = choose_random(vtCount);
        int idx2 = choose_random(vtCount);
        Edge e = gen_edge(idx1,idx2, vertices);
        edges[i] = e;
    }
    return edges;

}
