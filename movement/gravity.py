import pygame
import random
import time

G = (6.674 * 10**-11)

class Body():
    def __init__(self, x, y, mass, radius, vel_x, vel_y):
        self.radius = radius
        self.mass = mass
        self.x = x
        self.y = y
        self.vel_x = vel_x
        self.vel_y = vel_y
        self.last_timestep = time.time()

    def distance(self, body):
        return ((((self.x - body.x) ** 2) + ((self.y - body.y) ** 2)) ** .5)

    def render(self, display):
        pygame.draw.circle(display, white, (self.x, self.y), self.radius)

    def get_delta_time(self):
        current = time.time()
        result = current - self.last_timestep
        self.last_timestep = current
        return result

    def update_position(self):
        self.x += self.vel_x * self.delta_time
        self.y += self.vel_y * self.delta_time

    def update_velocity(self, bodies):
        self.delta_time = self.get_delta_time()

        m_1 = self.mass

        for body in bodies:
            if body == self:
                continue
            r =  self.distance(body)

            if r < self.radius + body.radius:
                if body.mass > self.mass:
                    return False

            if r < 20:
                continue

            m_2 = body.mass

            self.vel_x += ((G * m_2 / r ** 2) * (body.x - self.x) / r) * self.delta_time
            self.vel_y += ((G * m_2 / r ** 2) * (body.y - self.y) / r) * self.delta_time

        if (self.x > 1200 and self.vel_x > 0) or (self.x < 0 and self.vel_x < 0):
            self.vel_x *= -1
        if (self.y > 1000 and self.vel_y > 0) or (self.y < 0 and self.vel_y < 0):
            self.vel_y *= -1

        return True






pygame.init()

display = pygame.display.set_mode((1200, 1000))

white = (255, 255, 255)
red = (255, 0, 0)
black = (0, 0, 0)

bodies = []

for i in range(0,200):
    # would be better to calculate radius, volume, and then use this to calculate mass
    size_rnd = random.random() * .25
    size = (4.2 * 10**15) * size_rnd
    radius = size_rnd * 10
    bodies.append(Body(random.randint(0,1200), random.randint(0,1000), size, radius, random.randint(-100,100), random.randint(-100,100)))

size = (4.2 * 10**15) * 10
radius = 100

bodies.append(Body(600, 500, size, radius, 0,0))

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()

    display.fill(black)

    to_remove = []

    for body in bodies:
        if not body.update_velocity(bodies):
            to_remove.append(body)

    for body in to_remove:
        bodies.remove(body)

    for body in bodies:
        body.update_position()
        body.render(display)


    pygame.display.update()
