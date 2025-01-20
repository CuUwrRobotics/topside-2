/*******************************************
 * Project: Matrix Operations Library
 * File: v_math.h
 * Author: Tyler Cady
 * Created: 01.17.24
 * Last Modified: 01.17.24
 *******************************************/

#pragma once 
#include <iostream>

class v_math
{
    public:
        float dot(float* a, float* b, int size);
        void inv(float* M, float* M_inv, int N);
        // void hstack(float* M, float* C, float* goal_vec, float* c);
        
};