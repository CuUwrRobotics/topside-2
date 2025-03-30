#include <zmq.hpp>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <bindings.h>

struct NavigatorData
{
    bool led_status;
    float temperature;
    float pressure;
    bool leak_detected;
    ADCData adc;
    AxisData mag;
    AxisData accel;
    AxisData gyro;
};

NavigatorData get_navigator_data()
{
    init();
    NavigatorData data;
    data.led_status = get_led_status();
    data.temperature = get_temperature();
    data.pressure = get_pressure();
    data.leak_detected = get_leak_detected();
    data.adc = get_adc_data();
    data.mag = get_mag_data();
    data.accel = get_accel_data();
    data.gyro = get_gyro_data();
    return data;
}
/*
void send_navigator_data(NavigatorData data)
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUSH);
    socket.connect("tcp://localhost:5555");
    zmq::message_t message(sizeof(NavigatorData));
    memcpy(message.data(), &data, sizeof(NavigatorData));
    socket.send(message);
} */

int main()
{
    /*
    NavigatorData data = get_navigator_data();
    send_navigator_data(data);
    */

    init();
    get_led(UserLed::Led1);
}
