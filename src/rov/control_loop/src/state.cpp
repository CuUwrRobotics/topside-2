#include <control_loop/include/control_loop/state.hpp>
#include <sys/time.h>
#include <cstdlib>
#include <zmq.hpp>

float previous_time = 0;
float get_delta_t()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    if(previous_time == 0) return 0;
    float current = tv.tv_sec + (tv.tv_usec / 1000000);
    float delta = current - previous_time;
    previous_time = current;
    return delta;
}

zmq::context_t context{};
zmq::socket_t socket{context, ZMQ_SUB};
struct sensor_data *get_sensors()
{
    socket.connect("tcp://localhost:5555");
    zmq::message_t message{};
    socket.recv(message);
    struct sensor_data *data = (struct sensor_data*) message.data();
    return data;
}

struct computed_state *get_state()
{
    float delta = get_delta_t();

}