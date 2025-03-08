#include "pid.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
float PID::step(float measurement, float setpoint)
{
    // Calculate the error
    float error = setpoint - measurement;

    // Integral term
    integral += error * T;

    // Derivative term (filtered)
    float derivative = (error - err_prev) / T;
    derivative = (T_C * derivative + (T - T_C) * deriv_prev) / T;

    // Calculate the control output
    float command = Kp * error + Ki * integral + Kd * derivative;

    // Saturate the command
    command = std::clamp(command, min, max);

    // Anti-windup: limit the rate of change of the command
    if (command - command_sat_prev > max_rate)
        command = command_sat_prev + max_rate;
    else if (command - command_sat_prev < -max_rate)
        command = command_sat_prev - max_rate;

    // Save previous values for the next step
    err_prev = error;
    deriv_prev = derivative;
    command_sat_prev = command;
    command_prev = command;

    return command;
}

void ROV_OBJECT::step(float F_x, float F_y, float F_z)
{
    // /*Update the ROV's velocity and position based on the applied forces*/
    // v_x += (F_x - k * v_x) / m * T;
    // v_y += (F_y - k * v_y) / m * T;
    // v_z += (F_z - k * v_z) / m * T;

    // /* Update pos with velocity*/ 
    // x += v_x * T;
    // y += v_y * T;
    // z += v_z * T;

    /* Random garbage to compile with*/
    v_x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f - 5.0f;
    v_y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f - 5.0f;
    v_z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f - 5.0f;
    x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 200.0f - 100.0f;
    y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 200.0f - 100.0f;
    z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 200.0f - 100.0f;
}


float ROV_OBJECT::get_velocity_x() const { return v_x; }
float ROV_OBJECT::get_velocity_y() const { return v_y; }
float ROV_OBJECT::get_velocity_z() const { return v_z; }

float ROV_OBJECT::get_position_x() const { return x; }
float ROV_OBJECT::get_position_y() const { return y; }
float ROV_OBJECT::get_position_z() const { return z; }


