import numpy as np
import pygame
from pygame import joystick
import sys
import zmq
# Constants for initial angles
theta1 = np.radians(45)
theta2 = np.radians(45)
theta3 = np.radians(0)

# Define each vector m1, m2, m3, m4
m1 = np.array([
    [np.sin(theta3) * np.cos(theta1)],
    [np.sin(theta3) * np.sin(theta2)],
    [0]
])  # bottom right

m2 = np.array([
    [np.sin(theta3) * np.cos(theta1)],
    [np.sin(theta3) * np.sin(theta2)],
    [0]
])  # bottom left

m3 = np.array([
    [-np.sin(theta3) * np.cos(theta1)],
    [np.sin(theta3) * np.sin(theta2)],
    [0]
])  # top left

m4 = np.array([
    [np.sin(theta3) * np.cos(theta1)],
    [np.sin(theta3) * np.sin(theta2)],
    [0]
])  # top right
m5 = np.array([
    [0],
    [0],
    [1]
]) # right elevator 
m6 = np.array([
    [0],
    [0],
    [1]
]) # left elevator 

def setup_controller():
    pygame.init()
    pygame.joystick.init()

    joystick_count = pygame.joystick.get_count()
    print(f"Joystick count: {joystick_count}")

    if joystick_count == 0:
        print("No Controllers detected!")
        sys.exit()

    joystick = pygame.joystick.Joystick(0)
    joystick.init()

    print(f"Detected Controller: {joystick.get_name()}")

    return joystick

def get_joystick_input():
    # Initialize joystick values to zero
    s1 = [0, 0, 0, 0, 0, 0]  # for joystick 1 (up, down, rotate right, rotate left, *_)
    s2 = [0, 0, 0, 0, 0, 0]  # for joystick 2 (forward, backwards, strafe right, strafe left, *_)
    
    # Process events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        
        # Handle axis motion
        if event.type == pygame.JOYAXISMOTION:
            joystick_id = event.joy
            axis = event.axis
            value = event.value

            if joystick_id == 0:  # Joystick 1 (e.g., for up, down, rotate)
                if axis == 1:  # Vertical axis for up/down
                    s1[0] = value
                elif axis == 0:  # Horizontal axis for rotate left/right
                    s1[1] = value
            elif joystick_id == 1:  # Joystick 2 (e.g., for forward/backward, strafe)
                if axis == 1:  # Vertical axis for forward/backward
                    s2[0] = value
                elif axis == 0:  # Horizontal axis for strafe
                    s2[1] = value

    return s1, s2


def get_coefficients(goal_vec):
    # # ms is a list of all motor vectors
    # ms = [m1, m2, m3, m4, m5, m6]
    # M = np.hstack(ms)  # Combine all motor vectors into a matrix
    # c = np.linalg.lstsq(M, goal_vec, rcond=None)[0]  # Solve for coefficients
    # return c
    c1, c2, c3, c4, c5, c6 = np.zeros(6)
    C = [c1, c2, c3, c4 , c5, c6]
    print(C)
    M = np.hstack([m1, m2, m3, m4, m5, m6])
    print(M)
    j = np.dot(M, C)
    M_inv = np.linalg.pinv(M)

    print(M_inv)

    c = np.dot(M_inv, goal_vec)
    # return array as 32 bit bytes 
    return c.astype(np.float32).tobytes()
    # return c

def create_goal_vec(s1, s2):
    # Initialize goal vector
    goal_vec = np.array([0, 0, 0], dtype=float)  # x, y, z

    # Handle joystick 1 (s1) - up, down, rotate right, rotate left
    up, down, rotate_right, rotate_left, *_ = s1
    goal_vec[1] += up - down
    goal_vec[2] += rotate_right - rotate_left

    # Handle joystick 2 (s2) - forward, backward, strafe right, strafe left
    forward, backward, strafe_right, strafe_left, *_ = s2
    goal_vec[0] += strafe_right - strafe_left
    goal_vec[2] += forward - backward

    # Normalize goal vector if necessary
    if np.linalg.norm(goal_vec) > 0:
        goal_vec = goal_vec / np.linalg.norm(goal_vec)

    return goal_vec


def print_robot_orientation(goal_vec):
    # Print robot's orientation based on goal vector
    x, y, z = goal_vec
    if x == 1:
        print("Robot is facing forward")
    elif x == -1:
        print("Robot is facing backward")
    elif y == 1:
        print("Robot is facing up")
    elif y == -1:
        print("Robot is facing down")
    elif z == 1:
        print("Robot is rotating right")
    elif z == -1:
        print("Robot is rotating left")
    else:
        print("Robot is stationary")

if __name__ == "__main__":
    joystick = setup_controller()  # Initialize joystick
    context = zmq.Context()  
    socket = context.socket(zmq.PUB)
    socket.bind("tcp://*:5555")

    prev_coefficients = [0, 0, 0, 0, 0, 0]
    while True:
        s1, s2 = get_joystick_input()  # Get joystick inputs
        goal_vec = create_goal_vec(s1, s2)  # Generate goal vector based on inputs
        print_robot_orientation(goal_vec)  # Output robot's orientation
        c = get_coefficients(goal_vec)  # Calculate motor coefficients
        if c != prev_coefficients:
            socket.send(c)
            # print(c)
    pygame.quit()  # Quit pygame
    