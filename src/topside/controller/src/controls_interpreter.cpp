#include <controller/controls_interpreter.hpp>

#include <cstring>

ControlsInterpreter::ControlsInterpreter() : m_Controller(0x046d, 0xc21d), math()
{
    Controller c(0x046d, 0xc21d); // F310 vendor id and product id);
    c.setup();
}

ControlsInterpreter::~ControlsInterpreter()
{
    m_Controller.term();
}

void ControlsInterpreter::get_goal_vec(float coords[], float *goal_vec) const
{
    /* Goal vector gives the intended x,y,z position of the bot based on controller input */
    /**
     *  LJ: up, down, rotate right, rotate left
     *  RJ: forward, backward, strafe right, strafe left
     * Coords: [LJX, LJY, RJX, RJY]
     */
    goal_vec[1] += coords[0];
    goal_vec[2] += coords[1];
    goal_vec[0] += coords[2];
    goal_vec[2] += coords[3];
}

void ControlsInterpreter::get_coefficients(float goal_vec[], float *coeffs)
{
    // Define each vector m1, m2, m3, m4, m5, m6
    const float theta1 = 45.0f * M_PI / 180.0f; // Convert degrees to radians
    const float theta2 = 45.0f * M_PI / 180.0f;
    const float theta3 = 0.0f;

    // m1, m2, m3, m4 (same for bottom-left and bottom-right)
    float m1[3] = {sin(theta3) * cos(theta1), sin(theta3) * sin(theta2), 0.0f};
    float m2[3] = {sin(theta3) * cos(theta1), sin(theta3) * sin(theta2), 0.0f};
    float m3[3] = {-sin(theta3) * cos(theta1), sin(theta3) * sin(theta2), 0.0f};
    float m4[3] = {sin(theta3) * cos(theta1), sin(theta3) * sin(theta2), 0.0f};

    // m5, m6 (elevators)
    float m5[3] = {0.0f, 0.0f, 1.0f};
    float m6[3] = {0.0f, 0.0f, 1.0f};

    // Create the matrix M by stacking the vectors horizontally
    float M[18]; // 6 vectors of length 3
    memcpy(M, m1, sizeof(m1));
    memcpy(M + 3, m2, sizeof(m2));
    memcpy(M + 6, m3, sizeof(m3));
    memcpy(M + 9, m4, sizeof(m4));
    memcpy(M + 12, m5, sizeof(m5));
    memcpy(M + 15, m6, sizeof(m6));

    // Inverse of M
    float M_inv[18];
    math.inv(M, M_inv, 3); // 3 is the size of each vector

    // Solve for the coefficients using the inverse matrix
    for (int i = 0; i < 6; i++)
    {
        coeffs[i] = 0;
        for (int j = 0; j < 3; j++)
        {
            coeffs[i] += M_inv[i * 3 + j] * goal_vec[j];
        }
    }

    // Output the coefficients for debugging
    std::cout << "Coefficients: ";
    for (int i = 0; i < 6; i++)
    {
        std::cout << coeffs[i] << " ";
    }
    std::cout << std::endl;
}
