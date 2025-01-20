/*******************************************
 * Project: Controls interpreter for the ROV
 * File: controls_interpreter.h
 * Author: Tyler Cady
 * Created: 01.17.24
 * Last Modified: 01.17.24
 *******************************************/
#pragma once

#include "controller.h"
#include "v_math.h"
#include <iostream>
#include <cmath> // For sin and cos

using std::memcpy;
using std::sin;
using std::cos;

class ControlsInterpreter
{
public:
    ControlsInterpreter();
    ~ControlsInterpreter();
    
    void get_goal_vec(float coords[], float* goal_vec) const;
    void get_coefficients(float goal_vec[], float* coeffs);

    // Expose Controller accessors publicly
    bool initController() { return c.init(); }
    bool readControllerInput() { return c.read_input(); }
    void getJoystickCoords(float* coords) const { c.get_joysticks(coords); }
    void terminateController() { c.term(); }

private:
    Controller c;
    v_math math;
    float coeffs[6]; // Motor coefficients
};
