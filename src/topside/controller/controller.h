/** 
 * 
 */
#pragma once

#include <libusb-1.0/libusb.h>
#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <string>

using std::hex;
using std::dec;
using std::map;
using std::cerr;
using std::cout;
using std::endl;
using std::bitset;
using std::vector;
using std::stringstream;

class Controller
{
public:
    Controller(uint16_t vendor_id, uint16_t product_id);
    ~Controller();
    bool init();              /* Initialize connection */
    bool term();              /* Terminate connection */
    bool read_input();        /* Read in raw controller data */
    void get_joysticks(float* coords) const;
    void get_buttons() const;
    void parse_input();
    void setup(){findDevice();}

private:
    libusb_context *ctx;
    libusb_device_handle *dev_handle;
    uint16_t vendor_id;
    uint16_t product_id;
    uint8_t endpoint_in;
    vector<unsigned char> input_data;
    vector<unsigned char> prev_input_data;
    bool findDevice();
};