import pygame
import time


player_pos = (100, 100)
agent_pos = (200, 200)
agent_speed = 100
player_speed = 200

pygame.init()

screen_width = 800
screen_height = 600
screen = pygame.display.set_mode((screen_width, screen_height))

black = (0, 0, 0)
white = (255, 255, 255)

running = True
last_time = time.time()


def draw_players():
    pygame.draw.circle(screen, white, player_pos, 10)
    pygame.draw.circle(screen, white, agent_pos, 10)

def vector_length(p1):
    return (p1[0]**2 + p1[1]**2)**0.5

left = False

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    current_time = time.time()
    time_delta = current_time - last_time
    last_time = current_time

    position_delta = player_pos[0] - agent_pos[0], player_pos[1] - agent_pos[1]

    agent_pos = (
        agent_pos[0] + ((position_delta[0] / vector_length(position_delta)) * time_delta * agent_speed),
        agent_pos[1] + ((position_delta[1] / vector_length(position_delta)) * time_delta * agent_speed),
    )


    player_delta = (0,0)


    if player_pos[0] > screen_width and not left:
        left = True

    if player_pos[0] < 0 and left:
        left = False

    if left:
        player_delta = (-player_speed,0)
    else:
        player_delta = (player_speed,0)


    player_pos = (
            player_pos[0] + player_delta[0] * time_delta,
            player_pos[1] + player_delta[1] * time_delta
    )

    screen.fill(black)
    draw_players()
    pygame.display.update()

pygame.quit()
