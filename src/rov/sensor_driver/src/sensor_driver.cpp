#include <zmq.hpp>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <bindings.h>
#include <sensors.h>
#include <stdlib.h>

void send_navigator_data()
{
    zmq::context_t context{};
    zmq::socket_t socket{context, ZMQ_PUSH};
    socket.connect("tcp://localhost:5555");

    struct sensor_data *data = read_sensors();
    zmq::message_t message{data, sizeof(struct sensor_data)};
}

struct sensor_data *read_sensors()
{
    struct sensor_data *data = new struct sensor_data;
    
    AxisData acceleration = read_accel();
    data->a_x = acceleration.x;
    data->a_y = acceleration.y;
    data->a_z = acceleration.z;
    
    AxisData gyro = read_gyro();
    data->v_yaw = gyro.z;
    data->v_pitch = gyro.y;
    data->v_roll = gyro.x;

    data->pressure = read_pressure();

    return data;
}

int main()
{
    /*
    NavigatorData data = get_navigator_data();
    send_navigator_data(data);
    */

    init();
    get_led(UserLed::Led1);
}
