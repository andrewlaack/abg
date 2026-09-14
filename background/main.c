#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "draw.h"

#define VERTICES 100
#define EDGES 1000

int main(void)
{

    srand(time(0));
    InitWindow(5120, 1440, "Raylib background animation window");

    while (!WindowShouldClose())
    {
        Vertex* vertices = gen_vertices(VERTICES);
        Edge* edges = gen_edges(vertices, VERTICES, EDGES);
        BeginDrawing();
        ClearBackground(BLACK);
        draw_edges(edges,EDGES);
        draw_vertices(vertices,VERTICES);
        EndDrawing();
        free(vertices);
        free(edges);
    }

    CloseWindow();
    return 0;
}
