#include <algorithm>
#include <thread>
#include <chrono>
#include <ctime>
#include <time.h>
#include <iostream>
#include <cstdint>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "draw.h"

#define VERTICES 100
#define EDGES 1000

std::unordered_map<std::uintptr_t, std::vector<Edge*>> getMap(Vertex* verts, Edge* edges, int edgeCount, int vertCount) {

    std::unordered_map<std::uintptr_t, std::vector<Edge*>> res {};

    for(int i = 0; i < vertCount; ++i) {
        Vertex* vert = &verts[i];
        res[std::uintptr_t(vert)] = std::vector<Edge*>{};
    }


    for (int i = 0; i < edgeCount; ++i) {
        Edge& e = edges[i];
        res[std::uintptr_t(e.v1)].push_back(&e);
        res[std::uintptr_t(e.v2)].push_back(&e);
    }

    return res;
}

void visit_vertex(
    Vertex* v,
    const std::vector<Edge*>& edges,
    std::vector<Edge*>& visitHeap,
    std::unordered_set<std::uintptr_t>& visited
) {

    v->visited = true;

    visited.insert(uintptr_t(v));
    for(Edge* edge: edges) {
        visitHeap.push_back(edge);

        auto cmp = [](Edge* a, Edge* b) {
            // this makes it a min heap bc <
            return a->weight < b->weight;
        };

        std::push_heap(visitHeap.begin(), visitHeap.end(), cmp);
    }
    return;
}

// create vertices
// create weighted edge list
// associated edges with both vertices
    // undirected graph
// start with arbitrary element
    // push edges into an array
    // search array for smallest element
    // explore
int main(void)
{

    srand(time(0));
    InitWindow(5120, 1440, "Raylib background animation window");

    while (!WindowShouldClose())
    {
        Vertex* vertices = gen_vertices(VERTICES);
        Edge* edges = gen_edges(vertices, VERTICES, EDGES);
        auto mp = getMap(vertices,edges,EDGES,VERTICES);

        std::unordered_set<std::uintptr_t> visited {};
        std::vector<Edge*> visitHeap;

        visit_vertex(&vertices[0], mp[uintptr_t(&vertices[0])], visitHeap, visited);
        bool done = false;

        while(!done) {

            BeginDrawing();
            ClearBackground(BLACK);
            draw_edges(edges,EDGES);
            draw_vertices(vertices,VERTICES);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::vector<Edge*> currentHeap = visitHeap;
            visitHeap.clear();

            auto cmp = [](Edge* a, Edge* b) {
                return a->weight < b->weight;
            };
            std::pop_heap(visitHeap.begin(), visitHeap.end(), cmp);

            Edge* vis = visitHeap.back();
            visitHeap.pop_back();

            if(visited.find(uintptr_t(vis->v1)) == visited.end() && visited.find(uintptr_t(vis->v2)) == visited.end()) {
                continue;
            }

            if(visited.find(uintptr_t(vis->v1)) != visited.end() && visited.find(uintptr_t(vis->v2)) != visited.end()) {
                continue;
            }


            Vertex* visiting = nullptr;

            if(visited.find(uintptr_t(vis->v1)) == visited.end()){
                visited.insert(uintptr_t(vis->v1));
                visiting = vis->v1;
            } else {
                visited.insert(uintptr_t(vis->v2));
                visiting = vis->v2;
            }
            vis->traversed = true;
            visit_vertex(visiting, mp[uintptr_t(visiting)], visitHeap, visited);
        }

        free(vertices);
        free(edges);
    }

    CloseWindow();
    return 0;
}
