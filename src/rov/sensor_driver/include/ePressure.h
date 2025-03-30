/* Header for the external pressure sensor */
#pragma once
#ifndef E_PRESSURE_H
#define E_PRESSURE_H

#include <linux/i2c-dev.h>
#include <iostream>


class ePressure
{
    private: 
        int address; /* 0x76 by default */
        int bus; /* i2c-6 by default */
        uint32_t raw_pressure;
        void read();
        void init();
    public:
        ePressure(int bus, int address) {this->bus=bus; this->address=address;};
        ePressure(){bus=6; address=0x76;};
        ~ePressure();
        float get_ePressure();
};


#endif // E_PRESSURE_H