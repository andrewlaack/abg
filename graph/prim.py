import pygame
import time
import heapq
import random
import math

pygame.init()

display = pygame.display.set_mode((5120,1440))

VERTICES = 100
EDGES = 1000

white = (255, 255, 255)
red = (255, 0, 0)
black = (0, 0, 0)
grey = (100,100,100)
light_grey = (50,50,50)


class Vertex():
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.visited = False

    def draw_vertex(self,display):
        if self.visited:
            pygame.draw.circle(display, white, (self.x,self.y), 5)
        else:
            pygame.draw.circle(display, grey, (self.x,self.y), 5)

class Edge():
    def __init__(self, v1, v2):
        self.v1 = v1
        self.v2 = v2
        self.dist = math.sqrt(((v1.x - v2.x) ** 2) + ((v1.y - v2.y) ** 2))

    def draw_edge(self,display, c):
        pygame.draw.line(display, c, (self.v1.x,self.v1.y), (self.v2.x,self.v2.y), 1)

    def __lt__(self,otr):
        return self.dist < otr.dist


while True:
    graph = {}

    for i in range(0,VERTICES):
        x = random.random() * 5120
        y = random.random() * 1440
        graph[Vertex(x,y)] = []


    edge_list = []
    for i in range(0,EDGES):
        k1 = None
        k2 = None
        while k1 == k2:
            k1 = random.choice(list(graph.keys()))
            k2 = random.choice(list(graph.keys()))

        edge = Edge(k1,k2)
        graph[k1].append(edge)
        graph[k2].append(edge)
        edge_list.append(edge)


    edge_heap = []
    visited_vertices = set()

    mst = []

    start = random.choice(list(graph.keys()))
    start.visited = True
    visited_vertices.add(start)
    for edge in graph[start]:
        heapq.heappush(edge_heap, edge)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        display.fill(black)
        for edge in edge_list:
            edge.draw_edge(display, light_grey)
        for edge in mst:
            edge.draw_edge(display, white)
        for vertex in graph:
            vertex.draw_vertex(display)

        item = None
        while edge_heap:
            candidate = heapq.heappop(edge_heap)
            if (candidate.v1 in visited_vertices) != (candidate.v2 in visited_vertices):
                item = candidate
                break

        if item is None:
            pygame.display.update()
#            if len(visited_vertices) == VERTICES:
#                pygame.image.save(display, "out.jpg")
            break

        new_vertex = item.v2 if item.v1 in visited_vertices else item.v1
        visited_vertices.add(new_vertex)
        new_vertex.visited = True
        mst.append(item)
        for edge in graph[new_vertex]:
            heapq.heappush(edge_heap, edge)

        time.sleep(.1)
        pygame.display.update()
