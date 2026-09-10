import pygame
import time
import  math
import random

pygame.init()

WIDTH=500
HEIGHT=WIDTH

display = pygame.display.set_mode((WIDTH,HEIGHT))

DOTS = 1000
DOT_SIZE = 1

white = (255, 255, 255)
red = (255, 0, 0)
black = (0, 0, 0)
grey = (100,100,100)
light_grey = (50,50,50)


def distance(x_1,y_1,x_2,y_2):
    return math.sqrt(((x_1 - x_2) ** 2) + ((y_1  - y_2) ** 2))

positions = []
distances = []

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()

    display.fill(black)

    pygame.draw.circle(display, white, (int(WIDTH/2), int(HEIGHT/2)), WIDTH/2)

    out = 0
    inside = 0

    for i in range(0,DOTS):
        pos_x = random.random() * WIDTH
        pos_y = random.random() * WIDTH
        pos = (pos_x,pos_y)

        dist = distance(pos_x,pos_y,int(WIDTH/2), int(HEIGHT/2))

        if dist > WIDTH/2:
            out += 1
        else:
            inside += 1
        positions.append((pos_x,pos_y))
        distances.append(dist)

    for idx in range(0,len(positions)):
        pos = positions[idx]
        if distances[idx] > WIDTH/2:
            pygame.draw.circle(display, white, pos, DOT_SIZE)
        else:
            pygame.draw.circle(display, black, pos, DOT_SIZE)

    pygame.display.update()

    percent_in = inside / (inside + out)
    area_in = percent_in * WIDTH*HEIGHT
    pi = area_in / ((WIDTH/2) ** 2)

    print(pi)

    time.sleep(.1)
