// #include "control_loop.h"
#include <control_loop/pid.h>
#define TIME_STEP (1.0)

int main()
{
    // Current simulation time
    float t = 0;

    // Iteration counter
    int i = 0;

    // Setpoint and output of the first control loop
    float command1 = 0;
    float stp1 = 100;
    float z1 = 0;

    // Setpoint and output of the second control loop
    float command2 = 0;
    float stp2 = 50;
    float z2 = 0;

    // PID controller parameters for the first control loop
    struct PID pid1 = {1, 0.1, 5, 0.1, 1, TIME_STEP, 100, -100, 40, 0, 0, 0, 0, 0};

    // Object parameters for the first control loop
    struct ROV_Object rov1 = {1, 0.1, 100, -100, TIME_STEP, 0, 0};


}