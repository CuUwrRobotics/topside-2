import pygame
import numpy as np
import sys

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

def get_intended_direction(joystick): 
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if event.type == pygame.JOYAXISMOTION:

        # Get left joystick x and y values
                    left_x = joystick.get_axis(0)  # Left stick X (strafe left-right)
                    left_y = joystick.get_axis(1)  # Left stick Y (forward/backward)
                    
                    # Get right joystick x and y values
                    right_x = joystick.get_axis(2)  # Right stick X (rotation around the X-axis)
                    right_y = joystick.get_axis(3)  # Right stick Y (vertical up/down movement)

                    # Debug: Print axis values
                    print(f"left_x: {left_x}, left_y: {left_y}, right_x: {right_x}, right_y: {right_y}")

                    # Initialize the goal vector (x, y, z)
                    goal_vec = np.array([0.0, 0.0, 0.0])

                    # Left stick: Forward/Backward, Strafe left/right
                    goal_vec[0] = left_x  # X-axis for strafe left/right (-1.0 = left, 1.0 = right)
                    goal_vec[1] = left_y  # Y-axis for forward/backward (-1.0 = backward, 1.0 = forward)

                    # Right stick: Vertical movement up/down
                    goal_vec[2] = right_y  # Z-axis for up/down (-1.0 = down, 1.0 = up)
                    
                    # Rotation around the X-axis (affects Y and Z axes)
                    goal_vec[1] += right_x  # Rotation will affect Y (forward/backward)
                    goal_vec[2] -= right_x  # Rotation will affect Z (up/down)

        return goal_vec

def print_controller_input(joystick):
    clock = pygame.time.Clock()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            # Button Press Event
            if event.type == pygame.JOYBUTTONDOWN:
                print(f"Button {event.button} pressed")

            if event.type == pygame.JOYBUTTONUP:
                print(f"Button {event.button} released")

            # Axis Movement (e.g., joystick sticks)
            if event.type == pygame.JOYAXISMOTION:
                axis_value = joystick.get_axis(event.axis)  # Get the value of the axis
                print(f"Axis {event.axis} value: {axis_value}")

            # Hat Switch (D-pad)
            if event.type == pygame.JOYHATMOTION:
                print(f"Hat {event.hat} position: {event.value}")
        
        clock.tick(60)  # Limit to 60 frames per second

if __name__ == "__main__":
    joystick = setup_controller()

    while True:   
        # add a 100ms delay
        pygame.time.wait(100)
        # Assuming joystick is initialized and connected
        goal_direction = get_intended_direction(joystick)
        print("Intended direction vector:", goal_direction)
