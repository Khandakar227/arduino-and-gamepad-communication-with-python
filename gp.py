import pygame
from pygame.locals import *

pygame.init()
# Get the gamepad
joystick = pygame.joystick.Joystick(0)
joystick.init()
# Print the gamepad's name
print(joystick.get_name())

while True:
    for event in pygame.event.get():
        print(event)
