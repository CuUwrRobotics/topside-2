#pragma once

struct PID
{
    float Kp;              /* Proportional gain constant */
    float Ki;              /* Integral gain constant */
    float Kd;              /* Derivative gain constant */
    float Kaw;             /* Anti-windup gain constant */
    float T_C;             /* Time constant for derivative filtering */
    float T;               /* Time step */
    float max;             /* Max command */
    float min;             /* Min command */
    float max_rate;        /* Max rate of change of the command */
    float integral;        /* Integral term */
    float err_prev;        /* Previous error */
    float deriv_prev;      /* Previous derivative */
    float command_sat_prev;/* Previous saturated command */
    float command_prev;    /* Previous command */
};

void PID_Init(struct PID *pid, float Kp, float Ki, float Kd, float Kaw, float T_C, float T, float max, float min, float max_rate);
float PID_Step(struct PID *pid, float measurement, float setpoint);

struct ROV_Object
{
    float m;         /* ROV mass*/
    float k;         /* Damping Constant */
    float F_max;     /* Maximum force */
    float F_min;     /* Minimum force */
    float T;         /* Time step */
    float v;         /* Velocity */
    float z;         /* Position */
};
void ROV_Init(struct ROV_Object *rov, float m, float k, float F_max, float F_min, float T, float v, float z);
void ROV_Step(struct ROV_Object *rov, float F, float T);
