import pygame
import random
import time

red = (255, 0, 0)
white = (255,255,255)


NUM_BOIDS = 300

class Boid:

    pos_x = 0
    pos_y = 0
    vel_x = 100
    vel_y = 100
    delta_y = 0
    delta_x = 0
    max_velocity = 100
    ACC = 1

    NEARBY_DISTANCE = 40
    SEPERATION_DISTANCE = 10

    def __init__(self):
        self.pos_x = random.randint(0,500)
        self.pos_y = random.randint(0,500)
        self.last_time = time.time()
        self.vel_x = random.randint(-100,100)
        self.vel_y = random.randint(-100,100)

    def draw(self,display):
        pygame.draw.circle(display, white, (self.pos_x, self.pos_y), 2)

    def distance(self,otr):
        return ((self.pos_x - otr.pos_x) ** 2 + (self.pos_y - otr.pos_y) ** 2) ** .5

    def move(self):
        self.pos_x = self.pos_x + self.delta_x
        self.pos_y = self.pos_y + self.delta_y

    def compute_move(self, flock):

        if self.pos_x > 500 and self.vel_x > 0:
            self.vel_x *= -1

        if self.pos_x < 0 and self.vel_x < 0:
            self.vel_x *= -1

        if self.pos_y > 500 and self.vel_y > 0:
            self.vel_y *= -1

        if self.pos_y < 0 and self.vel_y < 0:
            self.vel_y *= -1

        nearby_headings = []
        nearby_positions = []
        too_close = []

        for i in range(0,len(flock)):
            if flock[i] == self:
                continue
            dist = self.distance(flock[i])

            if dist < self.SEPERATION_DISTANCE:
                too_close.append([flock[i].pos_x, flock[i].pos_y])
            if dist < self.NEARBY_DISTANCE:
                nearby_headings.append([flock[i].vel_x, flock[i].vel_y])
                nearby_positions.append([flock[i].pos_x, flock[i].pos_y])

        if nearby_positions:
            center_x = sum(p[0] for p in nearby_positions) / len(nearby_positions)
            center_y = sum(p[1] for p in nearby_positions) / len(nearby_positions)
            self.vel_x += (center_x - self.pos_x) * .08
            self.vel_y += (center_y - self.pos_y) * .08

        if nearby_headings:
            avg_x = sum(p[0] for p in nearby_headings) / len(nearby_headings)
            avg_y = sum(p[1] for p in nearby_headings) / len(nearby_headings)
            self.vel_x += (avg_x - self.vel_x) * .02
            self.vel_y += (avg_y - self.vel_y) * .02

        sep_x = 0
        sep_y = 0

        for pos in too_close:
            sep_x += self.pos_x - pos[0]
            sep_y += self.pos_y - pos[1]

        self.vel_x += sep_x * .04
        self.vel_y += sep_y * .04

        vel_current = ((self.vel_x ** 2) + (self.vel_y ** 2)) ** .5

        if vel_current > self.max_velocity:
            # make unit vector
            self.vel_x /= vel_current
            self.vel_y /= vel_current

            # make max speed
            self.vel_x *= self.max_velocity
            self.vel_y *= self.max_velocity

        current_time = time.time()

        self.vel_x += self.vel_x * (self.ACC * (current_time - self.last_time))
        self.vel_y += self.vel_y * (self.ACC * (current_time - self.last_time))

        self.delta_x = self.vel_x * (current_time - self.last_time)
        self.delta_y = self.vel_y * (current_time - self.last_time)
        self.last_time = current_time







pygame.init()

display = pygame.display.set_mode((500,500))

flock = []

for i in range(NUM_BOIDS):
    flock.append(Boid())

while True:
    
    display.fill(red)


    for boid in flock:
        boid.compute_move(flock)

    for boid in flock:
        boid.move()
        boid.draw(display)

    pygame.display.update()
