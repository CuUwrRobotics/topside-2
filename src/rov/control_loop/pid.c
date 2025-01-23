#include "pid.h"

/* Constructor for PID*/
void pid_init(struct PID *pid, float Kp, float Ki, float Kd, float Kaw, float T_C, float T, float max, float min, float max_rate)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->Kaw = Kaw;
    pid->T_C = T_C;
    pid->T = T;
    pid->max = max;
    pid->min = min;
    pid->max_rate = max_rate;
    pid->integral = 0.0f;
    pid->err_prev = 0.0f;
    pid->deriv_prev = 0.0f;
    pid->command_sat_prev = 0.0f;
    pid->command_prev = 0.0f;
}

/* PID_Step represents 1 step (every 100ms)*/
float PID_Step(struct PID *pid, float measurement, float setpoint)
{
    float err; 
    float cmd;
    float cmd_sat;
    float deriv_fltr;

    /* Calculate error */
    err = setpoint - measurement;

    /* Integral calculation */
    pid -> integral += pid -> Ki * pid -> T * err;
    /* Derivative Calc */
    deriv_fltr = (2 * pid -> T_C - pid -> T) / (2 * pid -> T_C + pid -> T);
    pid->err_prev = err;
    pid->deriv_prev = deriv_fltr;

    /* Sum the terms */
    cmd = pid-> Kp * err + pid->integral - pid->Kd * deriv_fltr;

    /* Saturate Command */
    if (cmd > pid->max)
    {
        cmd_sat = pid->max;
    }
    else if (cmd < pid->min)
    {
        cmd_sat = pid->min;
    }
    else
    {
        cmd_sat = cmd;
    }

    /* Rate limiter application */
    if (cmd_sat - pid->command_sat_prev > pid->max_rate)
    {
        cmd_sat = pid->command_sat_prev + pid->max_rate;
    }
    else if (cmd_sat - pid->command_sat_prev < -pid->max_rate)
    {
        cmd_sat = pid->command_sat_prev - pid->max_rate;
    }
    else
    {
        /* Nothing happened and the lord did grin*/
    }
    pid -> command_sat_prev = cmd_sat;
    return cmd_sat;
}
