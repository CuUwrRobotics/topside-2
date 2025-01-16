#include "controller_parser.h"
#include <iostream>

using namespace std;

Controller::Controller(uint16_t vendor_id, uint16_t product_id)
    : ctx(nullptr), dev_handle(nullptr), vendor_id(vendor_id), product_id(product_id), endpoint_in(0), input_data(64), prev_input_data(64)
{
    libusb_init(&ctx);
}

Controller::~Controller()
{
    term();
    libusb_exit(ctx);
}

bool Controller::findDevice()
{
    libusb_device **device_list;
    ssize_t cnt = libusb_get_device_list(ctx, &device_list);
    if (cnt < 0)
    {
        cerr << "Error: Unable to get device list" << endl;
        return false;
    }

    for (ssize_t i = 0; i < cnt; i++)
    {
        libusb_device_descriptor desc;
        int status = libusb_get_device_descriptor(device_list[i], &desc);
        if (status < 0)
        {
            continue;
        }

        if (desc.idVendor == vendor_id && desc.idProduct == product_id)
        {
            status = libusb_open(device_list[i], &dev_handle);
            if (status != 0)
            {
                cerr << "Error opening device" << endl;
                return false;
            }

            status = libusb_claim_interface(dev_handle, 0);
            if (status < 0)
            {
                cerr << "Error claiming interface." << endl;
                libusb_close(dev_handle);
                dev_handle = nullptr;
                return false;
            }

            endpoint_in = 0x81;
            return true;
        }
    }

    libusb_free_device_list(device_list, 1);
    return false;
}

bool Controller::init()
{

    return findDevice();
}

bool Controller::term()
{
    if (dev_handle)
    {
        libusb_release_interface(dev_handle, 0);
        libusb_close(dev_handle);
        dev_handle = nullptr;
    }
    return true;
}

bool Controller::read_input()
{
    int actual_length;
    int status = libusb_interrupt_transfer(dev_handle, endpoint_in, input_data.data(), input_data.size(), &actual_length, 0);
    if (status != 0)
    {
        cerr << "Error reading input data: " << status << endl;
        return false;
    }

    bool event_occurred = false;
    for (size_t i = 0; i < input_data.size(); ++i)
    {
        if (input_data[i] != prev_input_data[i])
        {
            event_occurred = true;
            break;
        }
    }

    if (event_occurred)
    {
        // print_state();
        parse_input(input_data);
    }

    prev_input_data = input_data;

    return true;
}

void Controller::print_joysticks() const
{
    /* Joysticks */

    /* Left Joy */
    // x axis is byte 6 & 7
    uint8_t left_joy_x1 = input_data[6];
    uint8_t left_joy_x2 = input_data[7];

    uint8_t left_joy_y1 = input_data[8];
    uint8_t left_joy_y2 = input_data[9];

    int16_t left_joy_x = (left_joy_x2 << 8) | left_joy_x1;
    int16_t left_joy_y = (left_joy_y2 << 8) | left_joy_y1;

    /* Right Joy */
    uint8_t right_joy_x1 = input_data[10];
    uint8_t right_joy_x2 = input_data[11];
    uint8_t right_joy_y1 = input_data[12];
    uint8_t right_joy_y2 = input_data[13];

    int16_t right_joy_x = (right_joy_x2 << 8) | right_joy_x1;
    int16_t right_joy_y = (right_joy_y2 << 8) | right_joy_y1;
     
    float lj_x_normed = -1.0f + ((left_joy_x - (-32767.0)) * (1-(-1)) / (32767.0 - -32767.0));
    float lj_y_normed = -1.0f + ((left_joy_y - (-32767.0)) * (1-(-1)) / (32767.0 - -32767.0));


    float rj_x_normed = -1.0f + ((right_joy_x - (-32767.0)) * (1-(-1)) / (32767.0 - -32767.0));
    float rj_y_normed = -1.0f + ((right_joy_y - (-32767.0)) * (1-(-1)) / (32767.0 - -32767.0));

    cout << "(" << (float)rj_x_normed << ", " << (float)rj_y_normed << ")" << endl;
    cout << "(" << (float)lj_x_normed << ", " << (float)lj_y_normed << ")" << endl;

}

void Controller::print_buttons() const
{
    uint8_t byte3 = input_data[2];
    uint8_t byte4 = input_data[3];
    uint8_t byte5 = input_data[4];
    uint8_t byte6 = input_data[5];
    /* D pad */
    uint8_t byte7 = input_data[6];
    uint8_t byte8 = input_data[7];
    uint8_t byte9 = input_data[8];
    uint8_t byte10 = input_data[9];
    
    /* Check byte 3 */
    if (byte3 != 0)
    {
        switch (byte3)
        {
        case 0x01:
            cout << "D_N button" << endl;
            break;
        case 0x02:
            cout << "D_S button" << endl;
            break;
        case 0x04:
            cout << "D_W button" << endl;
            break;
        case 0x05:
            cout << "D_NW button" << endl;
            break;
        case 0x06:
            cout << "D_SW button" << endl;
            break;
        case 0x08:
            cout << "D_E button" << endl;
            break;
        case 0x09:
            cout << "D_NE button" << endl;
            break;  
        case 0x0a:
            cout << "D_SE button" << endl;
            break;  
        case 0x10:
            cout << "Start button" << endl;
            break;
        case 0x20:
            cout << "Back button" << endl;
            break;
        case 0x40:
            cout << "Left Stick button" << endl;
            break;
        case 0x80:
            cout << "Right Stick button" << endl;
            break;
        }
    }

    /* Check byte 4 */
    if (byte4 != 0)
    {
        switch (byte4)
        {
        case 0xa0:
            cout << "Y & B button" << endl;
            break;
        case 0xc0:
            cout << "X & Y button" << endl;
            break;
        case 0x80:
            cout << "Y button" << endl;
            break;
        case 0x50:
            cout << "A & X button" << endl;
            break;
        case 0x40:
            cout << "X button" << endl;
            break;
        case 0x30:
            cout << "A & B buttons" << endl;
            break;
        case 0x20:
            cout << "B button" << endl;
            break;
        case 0x10:
            cout << "A button" << endl;
            break;
        case 0x04:
            cout << "Center button" << endl;
            break;
        case 0x03:
            cout << "LB & RB button" << endl;
            break;
        case 0x02:
            cout << "RB button" << endl;
            break;
        case 0x01:
            cout << "LB button" << endl;
            break;
        default:
            break;
        }
    }

    /* Check LT and RT pressures */
    if (byte5 != 0)
    {
        switch (byte5)
        {
        case 0xFF:
            cout << "LT button" << endl;
            break;
        default:
            float ltp = ((float)byte5 / 255.0) * 100;
            cout << "LT pressure: " << ltp << "%" << endl;
            break;
        }
    }

    if (byte6 != 0)
    {
        switch (byte6)
        {
        case 0xFF:
            cout << "RT button" << endl;
            break;
        default:
            float rtp = ((float)byte6 / 255.0) * 100;
            cout << "RT pressure: " << rtp << "%" << endl;
            break;
        }
    }
}

void Controller::parse_input(const vector<unsigned char> &data)
{
    print_joysticks();
    print_buttons();
    // print_state();
}

int main()
{
    Controller c(0x046d, 0xc21d); // F310 vendor id and product id

    if (c.init())
    {

        while (true)
        {
            if (!c.read_input())
            {
                break;
            }
        }
        c.term();
    }
    else
    {
        cerr << "Failed to initialize controller." << endl;
    }

    return 0;
}
