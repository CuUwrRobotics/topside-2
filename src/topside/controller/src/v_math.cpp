/*******************************************
 * Project: Matrix Operations Library
 * File: v_math.cpp
 * Author: Tyler Cady
 * Created: 01.17.24
 * Last Modified: 01.17.24
 *******************************************/

#include <controller/v_math.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <cstddef>

float v_math::dot(float *a, float *b, int size)
{
    float sum = 0;
    for (std::size_t idx = 0; idx < size; idx++)
    {
        sum += a[idx] * b[idx];
    }
    return sum;
}

void v_math::inv(float *M, float *M_inv, int N)
{
    float *augmented = new float[N * N * 2];
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            augmented[i * 2 * N + j] = M[i * N + j];
            augmented[i * 2 * N + N + j] = (i == j) ? 1.0f : 0.0f;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        int maxRow = i;
        for (int k = i + 1; k < N; ++k)
        {
            if (std::fabs(augmented[k * 2 * N + i]) > std::fabs(augmented[maxRow * 2 * N + i]))
            {
                maxRow = k;
            }
        }

        if (maxRow != i)
        {
            for (int k = 0; k < 2 * N; ++k)
            {
                std::swap(augmented[i * 2 * N + k], augmented[maxRow * 2 * N + k]);
            }
        }

        float diagValue = augmented[i * 2 * N + i];
        if (std::fabs(diagValue) < 1e-6f)
        {
            delete[] augmented;
            throw std::runtime_error("Matrix is singular and cannot be inverted.");
        }

        for (int k = 0; k < 2 * N; ++k)
        {
            augmented[i * 2 * N + k] /= diagValue;
        }

        for (int j = 0; j < N; ++j)
        {
            if (j != i)
            {
                float factor = augmented[j * 2 * N + i];
                for (int k = 0; k < 2 * N; ++k)
                {
                    augmented[j * 2 * N + k] -= factor * augmented[i * 2 * N + k];
                }
            }
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            M_inv[i * N + j] = augmented[i * 2 * N + N + j];
        }
    }

    delete[] augmented;
}
