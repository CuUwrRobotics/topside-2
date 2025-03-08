#include "pid.h"
#include "sensors.h"
#include <iostream>
#include <unistd.h>

sensor_data get_data(int readfd, sensor_data *data){
    // initialize a pipe big enough to hold the data
    if (read(readfd, data, sizeof(sensor_data)) < 0){
        std::cerr << "Error reading from pipe" << std::endl;
        exit(1);
    }
    else{
        return *data;
    }
}

int main()
{
    // Create PID controllers for each velocity component (x, y, z)
    PID pid_x(1.0f, 0.1f, 0.5f, 0.0f, 0.1f, 0.01f, 10.0f, -10.0f, 1.0f);
    PID pid_y(1.0f, 0.1f, 0.5f, 0.0f, 0.1f, 0.01f, 10.0f, -10.0f, 1.0f);
    PID pid_z(1.0f, 0.1f, 0.5f, 0.0f, 0.1f, 0.01f, 10.0f, -10.0f, 1.0f);

    // Create ROV object
    float mass = 5.44f; // approx. Mass of the ROV in kg (~12lbs)
    float damping = 0.1f; // Damping constant for water
    float m = 5.44f;       // ROV mass
    float k = 0.1f;       // Damping constant (TODO: Figure out what this is)
    float F_max = 0.0f;   // Maximum force
    float F_min = 0.0f;   // Minimum force
    float T = 0.01f;       // Time step
    float v_x = 0;     // Velocity in x
    float v_y = 0;     // Velocity in y
    float v_z = 0;     // Velocity in z
    float x = 0;       // Position in x
    float y = 0;       // Position in y
    float z = 0;       // Position in z

    ROV_Object rov();

    // Set target velocities (setpoints)
    float setpoint_x = 1.0f; // Target velocity in x direction
    float setpoint_y = 1.0f; // Target velocity in y direction
    float setpoint_z = 1.0f; // Target velocity in z direction

    for (int i = 0; i < 1000; ++i)
    {
        // Calculate control forces using PID controllers
        float force_x = pid_x.step(rov.get_velocity_x(), setpoint_x);
        float force_y = pid_y.step(rov.get_velocity_y(), setpoint_y);
        float force_z = pid_z.step(rov.get_velocity_z(), setpoint_z);

        // Apply the forces to the ROV
        rov.step(force_x, force_y, force_z);

        // Output the current velocities and forces
        std::cout << "Time: " << i * rov.get_position_x() << ", Velocity (x,y,z): (" 
                  << rov.get_velocity_x() << ", " << rov.get_velocity_y() << ", " << rov.get_velocity_z() 
                  << "), Force (x,y,z): (" << force_x << ", " << force_y << ", " << force_z << ")" << std::endl;
    }

    return 0;
}
