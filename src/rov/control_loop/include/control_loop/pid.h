#pragma once

#include <algorithm>

class PID
{
    private:
        float Kp;                  /* Proportional gain constant */
        float Ki;                  /* Integral gain constant */
        float Kd;                  /* Derivative gain constant */ 
        float Kaw;                 /* Anti-windup gain constant */ 
        float T_C;                 /* Time constant for derivative filtering */ 
        float T;                   /* Time step */
        float max;                 /* Max command */
        float min;                 /* Min command */
        float max_rate;            /* Max rate of change of the command */
        float integral;            /* Integral term */
        float err_prev;            /* Previous error */
        float deriv_prev;          /* Previous derivative */
        float command_sat_prev;    /* Previous saturated command */
        float command_prev;        /* Previous command */ 

    public:
        PID(float Kp, float Ki, float Kd, float Kaw, float T_C, float T, float max, float min, float max_rate)
            : Kp(Kp), Ki(Ki), Kd(Kd), Kaw(Kaw), T_C(T_C), T(T), max(max), min(min), max_rate(max_rate),
            integral(0.0f), err_prev(0.0f), deriv_prev(0.0f), command_sat_prev(0.0f), command_prev(0.0f)
        {}

        float step(float measurement, float setpoint);
};

class ROV_Object
{
    private:
        float m;       /* ROV mass */ 
        float k;       /* Damping constant */
        float F_max;   /* Maximum force */ 
        float F_min;   /* Minimum force */ 
        float T;       /* Time step */
        float v_x;     /* Velocity in x */
        float v_y;     /* Velocity in y */
        float v_z;     /* Velocity in z */
        float x;       /* Position in x */
        float y;       /* Position in y */
        float z;       /* Position in z */ 

    public:
        ROV_Object(float m, float k, float F_max, float F_min, float T, float v_x, float v_y, float v_z, float x, float y, float z)
            : m(m), k(k), F_max(F_max), F_min(F_min), T(T), v_x(v_x), v_y(v_y), v_z(v_z), x(x), y(y), z(z)
        {}

        void step(float F_x, float F_y, float F_z)
        {
            /* Update the ROV's velocity and position based on the applied forces */ 
            v_x += (F_x - k * v_x) / m * T;
            v_y += (F_y - k * v_y) / m * T;
            v_z += (F_z - k * v_z) / m * T;

            /* Update position based on velocity */
            x += v_x * T;
            y += v_y * T;
            z += v_z * T;
        }

        /* Getter functions for velocity and position */ 
        float get_velocity_x() const; 
        float get_velocity_y() const; 
        float get_velocity_z() const; 

        float get_position_x() const; 
        float get_position_y() const; 
        float get_position_z() const; 
};

