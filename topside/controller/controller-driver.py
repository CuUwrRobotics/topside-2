import pygame
import zmq
import sys


def setup_controller():
    pygame.init()
    pygame.joystick.init()

    joystick_count = pygame.joystick.get_count()

    if joystick_count == 0:
        print("No Controllers detected!")
        sys.exit()

    joystick = pygame.joystick.Joystick(0)
    joystick.init()

    print(f"Detected Controller: {joystick.get_name()}")


def print_controller_input():
    while True:
        # Process events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            # Check for button press
            if event.type == pygame.JOYBUTTONDOWN:
                print(f"Button {event.button} pressed")

            if event.type == pygame.JOYBUTTONUP:
                print(f"Button {event.button} released")
            
            # Check for axis movement (sticks)
            if event.type == pygame.JOYAXISMOTION:
                print(f"Axis {event.axis} value: {event.value}")
            
            # Check for hat switch (D-pad)
            if event.type == pygame.JOYHATMOTION:
                print(f"Hat {event.hat} position: {event.value}")

def send_controller_input():
    # send controller inputs to motor driver via ZMQ
    context = zmq.Context()
    socket = context.socket(zmq.PUB)
    socket.bind("tcp://*:5555")
    while True:
        # Process events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            # Check for button press
            if event.type == pygame.JOYBUTTONDOWN:
                socket.send_string(f"Button {event.button} pressed")

            if event.type == pygame.JOYBUTTONUP:
                socket.send_string(f"Button {event.button} released")
            
            # Check for axis movement (sticks)
            if event.type == pygame.JOYAXISMOTION:
                socket.send_string(f"Axis {event.axis} value: {event.value}")
            
            # Check for hat switch (D-pad)
            if event.type == pygame.JOYHATMOTION:
                socket.send_string(f"Hat {event.hat} position: {event.value}")
    

if __name__ == "__main__":
    send_controller_input()
    # print_controller_input()