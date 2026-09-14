#include "vert.h"

typedef struct Edge {
    Vertex* v1;
    Vertex* v2;

} Edge;

Edge gen_edge(int idx1, int idx2, Vertex* vertices);
Edge* gen_edges(Vertex* vertices, int vtCount, int edgeCount);
void print_edge(Edge* e);
