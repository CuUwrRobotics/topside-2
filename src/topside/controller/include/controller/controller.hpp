/**
 *
 */
#pragma once

#include <libusb-1.0/libusb.h>
#include <iostream>
#include <vector>
#include <cstdint>
#include <bitset>
#include <map>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <string>

class Controller
{
public:
    Controller(std::uint16_t vendor_id, std::uint16_t product_id);
    ~Controller();
    bool init();       /* Initialize connection */
    bool term();       /* Terminate connection */
    bool read_input(); /* Read in raw controller data */
    void get_joysticks(float *coords) const;
    void get_buttons() const;
    void parse_input();
    void setup() { findDevice(); }

private:
    ::libusb_context *m_USBContext;
    ::libusb_device_handle *m_DeviceHandle;
    std::uint16_t m_VendorID;
    std::uint16_t m_ProductID;
    std::uint8_t endpoint_in;
    std::vector<std::uint8_t> m_InputData;
    std::vector<std::uint8_t> m_PreviousInputData;
    bool findDevice();
};
