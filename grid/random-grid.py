import pygame, sys
import random
from pygame.locals import *

pygame.init()

RED = (255,0,0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

Y=5
X=5

WIDTH = 500
HEIGHT = 500

DISPLAY = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Hello World!')



grid = [
    [0,0,0,0,0],
    [0,1,1,0,0],
    [0,1,1,0,0],
    [0,0,0,1,0],
    [1,0,0,0,0]
]

def simulate(prior):
    neighbors = prior.copy()

    for y in range(len(prior)):
        for x in range(len(prior[y])):
            neighbors[y][x] = random.randint(0,2)

    return neighbors


def drawGrid():
    blockSize = int(WIDTH / len(grid))
    for x in range(0, WIDTH, blockSize):
        for y in range(0, HEIGHT, blockSize):
            if grid[int(x / blockSize)][int(y / blockSize)] == 1:
                rect = pygame.Rect(x, y, blockSize, blockSize)
                pygame.draw.rect(DISPLAY, WHITE, rect)
            else:
                rect = pygame.Rect(x, y, blockSize, blockSize)
                pygame.draw.rect(DISPLAY, WHITE, rect, 1)



while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()

    grid = simulate(grid)
    DISPLAY.fill(BLACK)
    drawGrid()
    pygame.display.update()

