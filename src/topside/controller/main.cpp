#include "controls_interpreter.h"
#include <iostream>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::milliseconds

int main() {
    ControlsInterpreter interpreter;

    if (interpreter.initController()) {
        float coords[4] = {0.0f, 0.0f, 0.0f, 0.0f}; // Placeholder for joystick data
        float goal_vec[3] = {0.0f, 0.0f, 0.0f};     // Placeholder for the goal vector
        float coeffs[6] = {0.0f};                   // Placeholder for coefficients

        while (true) {
            // Read input from the controller
            if (!interpreter.readControllerInput()) {
                std::cerr << "Failed to read input from controller. Exiting..." << std::endl;
                break;
            }

            // Get joystick coordinates
            interpreter.getJoystickCoords(coords);

            // Compute the goal vector
            interpreter.get_goal_vec(coords, goal_vec);

            // Compute the coefficients
            interpreter.get_coefficients(goal_vec, coeffs);

            // For this test, we'll print the joystick coords, goal vector, and coefficients
            std::cout << "Joystick Coordinates: [";
            for (int i = 0; i < 4; ++i) {
                std::cout << coords[i] << (i < 3 ? ", " : "]\n");
            }

            std::cout << "Goal Vector: [";
            for (int i = 0; i < 3; ++i) {
                std::cout << goal_vec[i] << (i < 2 ? ", " : "]\n");
            }

            std::cout << "Coefficients: [";
            for (int i = 0; i < 6; ++i) {
                std::cout << coeffs[i] << (i < 5 ? ", " : "]\n");
            }

            // Optional: Add a short delay for testing purposes
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        interpreter.terminateController();
    } else {
        std::cerr << "Failed to initialize the controller. Exiting..." << std::endl;
    }

    return 0;
}
