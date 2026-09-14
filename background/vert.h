typedef struct Vert {
    int x;
    int y;

} Vertex;
Vertex gen_vertex();
Vertex* gen_vertices(int vtCount);
Vertex* choose_random(Vertex* vertices, int length);
