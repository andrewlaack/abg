import pygame
import time
import heapq
import random
import math

pygame.init()

display = pygame.display.set_mode((5120,1440))

VERTICES = 1000
EDGES = 1000

white = (255, 255, 255)
red = (255, 0, 0)
black = (0, 0, 0)
grey = (100,100,100)
light_grey = (0,0,0)


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

done = False



start_node = list(graph.keys())[0]
start_node.visited = True

to_visit = []
next_visit = [start_node]

visited_edges = []
already_seen = set()


while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()

    display.fill(black)
    for vertex in graph:
        vertex.draw_vertex(display)
    for edge in edge_list:
        edge.draw_edge(display, light_grey)
    for edge in visited_edges:
        edge.draw_edge(display, white)

    if done:
        pygame.display.update()
        pygame.image.save(display, "out.jpg")
        break

    to_visit = next_visit
    next_visit = []
    for next_node in to_visit:
        next_node.visited = True
        for edge in graph[next_node]:
            visited_edges.append(edge)
            if not edge.v2 in already_seen:
                next_visit.append(edge.v2)
                already_seen.add(edge.v2)

    time.sleep(1)
    pygame.display.update()
