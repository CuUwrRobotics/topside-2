#include <controller/controller.hpp>

#include <iostream>
#include <cstddef>
#include <cstdint>

#include <libusb-1.0/libusb.h>

Controller::Controller(std::uint16_t vendor_id, std::uint16_t product_id)
    : m_USBContext(nullptr), m_DeviceHandle(nullptr), m_VendorID(vendor_id), m_ProductID(product_id), endpoint_in(0), m_InputData(64), m_PreviousInputData(64)
{
    ::libusb_init(&m_USBContext);
}

Controller::~Controller()
{
    term();
    ::libusb_exit(m_USBContext);
}

bool Controller::findDevice()
{
    ::libusb_device **device_list;
    std::size_t count = ::libusb_get_device_list(m_USBContext, &device_list);
    if (count < 0)
    {
        std::cerr << "Error: Unable to get device list" << std::endl;
        return false;
    }

    for (std::size_t idx = 0; idx < count; idx++)
    {
        ::libusb_device_descriptor desc;
        int status = ::libusb_get_device_descriptor(device_list[idx], &desc);
        if (status < 0)
        {
            continue;
        }

        if (desc.idVendor == m_VendorID && desc.idProduct == m_ProductID)
        {
            status = ::libusb_open(device_list[idx], &m_DeviceHandle);
            if (status != 0)
            {
                std::cerr << "Error opening device" << std::endl;
                return false;
            }

            status = libusb_claim_interface(m_DeviceHandle, 0);
            if (status < 0)
            {
                std::cerr << "Error claiming interface." << std::endl;
                ::libusb_close(m_DeviceHandle);
                m_DeviceHandle = nullptr;
                return false;
            }

            endpoint_in = 0x81;
            return true;
        }
    }

    ::libusb_free_device_list(device_list, 1);
    return false;
}

bool Controller::init()
{
    return findDevice();
}

bool Controller::term()
{
    if (m_DeviceHandle)
    {
        ::libusb_release_interface(m_DeviceHandle, 0);
        ::libusb_close(m_DeviceHandle);
        m_DeviceHandle = nullptr;
    }
    return true;
}

bool Controller::read_input()
{
    int actual_length;
    int status = ::libusb_interrupt_transfer(m_DeviceHandle, endpoint_in, m_InputData.data(), m_InputData.size(), &actual_length, 0);
    if (status != 0)
    {
        std::cerr << "Error reading input data: " << status << std::endl;
        return false;
    }

    bool event_occurred = false;
    for (std::size_t idx = 0; idx < m_InputData.size(); ++idx)
    {
        if (m_InputData[idx] != m_PreviousInputData[idx])
        {
            event_occurred = true;
            break;
        }
    }

    if (event_occurred)
    {
        // print_state();
        parse_input();
    }

    m_PreviousInputData = m_InputData;

    return true;
}

void Controller::get_joysticks(float *coords) const
{
    // Constants for normalization
    constexpr float JOY_MIN = -32767.0f;
    constexpr float JOY_MAX = 32767.0f;

    // Left joystick
    std::uint8_t left_joy_x1 = m_InputData[6];
    std::uint8_t left_joy_x2 = m_InputData[7];
    std::uint8_t left_joy_y1 = m_InputData[8];
    std::uint8_t left_joy_y2 = m_InputData[9];

    std::int16_t left_joy_x = (left_joy_x2 << 8) | left_joy_x1;
    std::int16_t left_joy_y = (left_joy_y2 << 8) | left_joy_y1;

    // Right joystick
    std::uint8_t right_joy_x1 = m_InputData[10];
    std::uint8_t right_joy_x2 = m_InputData[11];
    std::uint8_t right_joy_y1 = m_InputData[12];
    std::uint8_t right_joy_y2 = m_InputData[13];

    std::int16_t right_joy_x = (right_joy_x2 << 8) | right_joy_x1;
    std::int16_t right_joy_y = (right_joy_y2 << 8) | right_joy_y1;

    // Normalize joystick values to range [-1, 1]
    coords[0] = (left_joy_x - JOY_MIN) / (JOY_MAX - JOY_MIN) * 2.0f - 1.0f;  // Left joystick X
    coords[1] = (left_joy_y - JOY_MIN) / (JOY_MAX - JOY_MIN) * 2.0f - 1.0f;  // Left joystick Y
    coords[2] = (right_joy_x - JOY_MIN) / (JOY_MAX - JOY_MIN) * 2.0f - 1.0f; // Right joystick X
    coords[3] = (right_joy_y - JOY_MIN) / (JOY_MAX - JOY_MIN) * 2.0f - 1.0f; // Right joystick Y

    // cout << "(" << (float)rj_x_normed << ", " << (float)rj_y_normed << ")" << endl;
    // cout << "(" << (float)lj_x_normed << ", " << (float)lj_y_normed << ")" << endl;
}

void Controller::get_buttons() const
{
    std::uint8_t byte3 = m_InputData[2];
    std::uint8_t byte4 = m_InputData[3];
    std::uint8_t byte5 = m_InputData[4];
    std::uint8_t byte6 = m_InputData[5];
    /* D pad */
    std::uint8_t byte7 = m_InputData[6];
    std::uint8_t byte8 = m_InputData[7];
    std::uint8_t byte9 = m_InputData[8];
    std::uint8_t byte10 = m_InputData[9];

    /* Check byte 3 */
    if (byte3 != 0)
    {
        switch (byte3)
        {
        case 0x01:
            std::cout << "D_N button" << std::endl;
            break;
        case 0x02:
            std::cout << "D_S button" << std::endl;
            break;
        case 0x04:
            std::cout << "D_W button" << std::endl;
            break;
        case 0x05:
            std::cout << "D_NW button" << std::endl;
            break;
        case 0x06:
            std::cout << "D_SW button" << std::endl;
            break;
        case 0x08:
            std::cout << "D_E button" << std::endl;
            break;
        case 0x09:
            std::cout << "D_NE button" << std::endl;
            break;
        case 0x0a:
            std::cout << "D_SE button" << std::endl;
            break;
        case 0x10:
            std::cout << "Start button" << std::endl;
            break;
        case 0x20:
            std::cout << "Back button" << std::endl;
            break;
        case 0x40:
            std::cout << "Left Stick button" << std::endl;
            break;
        case 0x80:
            std::cout << "Right Stick button" << std::endl;
            break;
        }
    }

    /* Check byte 4 */
    if (byte4 != 0)
    {
        switch (byte4)
        {
        case 0xa0:
            std::cout << "Y & B button" << std::endl;
            break;
        case 0xc0:
            std::cout << "X & Y button" << std::endl;
            break;
        case 0x80:
            std::cout << "Y button" << std::endl;
            break;
        case 0x50:
            std::cout << "A & X button" << std::endl;
            break;
        case 0x40:
            std::cout << "X button" << std::endl;
            break;
        case 0x30:
            std::cout << "A & B buttons" << std::endl;
            break;
        case 0x20:
            std::cout << "B button" << std::endl;
            break;
        case 0x10:
            std::cout << "A button" << std::endl;
            break;
        case 0x04:
            std::cout << "Center button" << std::endl;
            break;
        case 0x03:
            std::cout << "LB & RB button" << std::endl;
            break;
        case 0x02:
            std::cout << "RB button" << std::endl;
            break;
        case 0x01:
            std::cout << "LB button" << std::endl;
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
            std::cout << "LT button" << std::endl;
            break;
        default:
            float ltp = ((float)byte5 / 255.0) * 100;
            std::cout << "LT pressure: " << ltp << "%" << std::endl;
            break;
        }
    }

    if (byte6 != 0)
    {
        switch (byte6)
        {
        case 0xFF:
            std::cout << "RT button" << std::endl;
            break;
        default:
            float rtp = ((float)byte6 / 255.0) * 100;
            std::cout << "RT pressure: " << rtp << "%" << std::endl;
            break;
        }
    }
}

void Controller::parse_input()
{
    float coords[4];
    get_joysticks(coords);
    get_buttons();
    // print_state();
}

// int main()
// {
//     Controller c(0x046d, 0xc21d); // F310 vendor id and product id

//     if (c.init())
//     {

//         while (true)
//         {
//             if (!c.read_input())
//             {
//                 break;
//             }
//         }
//         c.term();
//     }
//     else
//     {
//         cerr << "Failed to initialize controller." << endl;
//     }

//     return 0;
// }
