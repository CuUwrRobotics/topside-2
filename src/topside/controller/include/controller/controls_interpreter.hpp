/*******************************************
 * Project: Controls interpreter for the ROV
 * File: controls_interpreter.h
 * Author: Tyler Cady
 * Created: 01.17.24
 * Last Modified: 01.17.24
 *******************************************/
#pragma once

#include <iostream>
#include <cmath> // For sin and cos

#include <controller/controller.hpp>
#include <controller/v_math.hpp>

class ControlsInterpreter
{
public:
    ControlsInterpreter();
    ~ControlsInterpreter();

    void get_goal_vec(float coords[], float *goal_vec) const;
    void get_coefficients(float goal_vec[], float *coeffs);

    // Expose Controller accessors publicly
    bool initialize_controller() { return m_Controller.init(); }
    bool read_controller_input() { return m_Controller.read_input(); }
    void get_joystick_coordinates(float *coords) const { m_Controller.get_joysticks(coords); }
    void terminate_controller() { m_Controller.term(); }

private:
    Controller m_Controller;
    v_math math;     // ?: Why is this a class?
    float coeffs[6]; // Motor coefficients
};
