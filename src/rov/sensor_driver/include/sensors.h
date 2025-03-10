#pragma once

struct sensor_data {
    float a_x;
    float a_y;
    float a_z;

    float v_yaw;
    float v_pitch;
    float v_roll;

    float pressure;
};

struct computed_state {
    float x;
    float y;
    float z;
    float v_x;
    float v_y;
    float v_z;
    float a_x;
    float a_y;
    float a_z;
    float yaw;
    float pitch;
    float roll;
    float v_yaw;
    float v_pitch;
    float a_roll;
};