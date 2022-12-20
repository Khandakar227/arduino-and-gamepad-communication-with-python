from bt import socket
import pygame
from pygame.locals import *
from time import asctime, localtime
# Game pad buttons
left_thumb_x = left_thumb_y = right_thumb_x = right_thumb_y = 0
btn = 0
hat_x = hat_y = 0
start = 9   # button 9 is the start button for my gamepad
# Intialize pygame
pygame.init()
# Get the gamepad
joystick = pygame.joystick.Joystick(0)
joystick.init()
# Print the gamepad's name
print(joystick.get_name())

while True:
    for event in pygame.event.get():

        if event.type == JOYAXISMOTION:
            left_thumb_x = int(joystick.get_axis(0)*100)
            left_thumb_y = int(joystick.get_axis(1)*100)
            right_thumb_y = int(joystick.get_axis(2)*100)
            right_thumb_x = int(joystick.get_axis(3)*100)

        if event.type == JOYBUTTONDOWN:
            btn = 1 if joystick.get_button(0) else 2 if joystick.get_button(1) else 3 if joystick.get_button(2) else 4 if joystick.get_button(
                3) else 5 if joystick.get_button(4) else 6 if joystick.get_button(5) else 7 if joystick.get_button(6) else 8 if joystick.get_button(7) else 0

        if event.type == JOYBUTTONUP:
            btn = 0

        if event.type == JOYHATMOTION:
            hat_x = joystick.get_hat(0)[0]
            hat_y = joystick.get_hat(0)[1]

        data = f"{btn},{left_thumb_x},{left_thumb_y},{right_thumb_x},{right_thumb_y}\n"

        socket.send(data)
        print("Data sent..", asctime(localtime()))

# Axis 0 = left thumb x, -1 to top and 1 to bottom
# Axis 1 = left thumb y, -1 to top and 1 to bottom
# Axis 2 = right thumb x, -1 to top and 1 to bottom
# Axis 3 = right thumb y, -1 to top and 1 to bottom
