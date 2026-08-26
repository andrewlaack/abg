import pygame
import random
import pygame.locals
import sys


grid_size = int(sys.argv[1])
living = int(sys.argv[2])


pygame.init()

WIDTH = 1500
HEIGHT = 1500

WHITE = (255,255,255)
BLACK = (0,0,0)

DISPLAY = pygame.display.set_mode((WIDTH,HEIGHT), pygame.RESIZABLE)


def simulate(prior):
    result = [row[:] for row in prior]

    count = 0

    for y in range(len(prior)):
        for x in range(len(prior[y])):
            neighbors = 0
            for dx in range(-1,2):
                for dy in range(-1,2):
                    if dx == 0 and dy == 0:
                        continue
                    if dx + x < 0 or dx + x >= len(prior[y]):
                        continue
                    if dy + y < 0 or dy + y >= len(prior):
                        continue
                    neighbors += prior[dy+y][dx+x]
            is_alive = prior[y][x]
            if neighbors == 3 or (is_alive and neighbors == 2):
                result[y][x] = 1
                count += 1
            else:
                # this is a copy of input...
                result[y][x] = 0

    return result


def drawGrid(g):
    blockSize = int(WIDTH / len(g))
    for y in range(0, WIDTH, blockSize):
        for x in range(0, HEIGHT, blockSize):
            if g[int(y / blockSize)][int(x / blockSize)] == 1:
                rect = pygame.Rect(x, y, blockSize, blockSize)
                pygame.draw.rect(DISPLAY, WHITE, rect)
            else:
                rect = pygame.Rect(x, y, blockSize, blockSize)
                pygame.draw.rect(DISPLAY, BLACK, rect)


grid = [[0] * grid_size for _  in range(grid_size)]

def seed(grid):
    for i in range(0,living):
        rnd_y = random.randint(0,len(grid) - 1)
        rnd_x = random.randint(0,len(grid[0]) - 1)
        grid[rnd_y][rnd_x] = 1

seed(grid)

while True:
    for event in pygame.event.get():
        if event.type == pygame.locals.QUIT:
            pygame.quit()
            exit()

    grid = simulate(grid)

    DISPLAY.fill(BLACK)
    drawGrid(grid)
    pygame.display.update()
