#include <control_loop/include/control_loop/state.hpp>
#include <sys/time.h>
#include <cstdlib>
#include <zmq.hpp>
#include <stdlib.h>

std::chrono::high_resolution_clock::time_point prev_time{};
float get_delta_t()
{
    std::chrono::high_resolution_clock::time_point current_time
        = std::chrono::high_resolution_clock::now();
    
    if(prev_time.time_since_epoch() == std::chrono::seconds::zero) return 0; // i dont think this line works
    return (std::chrono::duration_cast<std::chrono::milliseconds>(current_time - prev_time).count() / 1000.0);
}

zmq::context_t context{};
zmq::socket_t socket{context, ZMQ_SUB};
struct sensor_data *get_sensors()
{
    socket.connect("tcp://localhost:5555");
    zmq::message_t message{};
    socket.recv(message);
    struct sensor_data *data = new (struct sensor_data);
    std::memcpy(data, message.data(), sizeof(struct sensor_data));
    return data;
}

struct computed_state *prev_state = NULL;
struct computed_state *get_state()
{
    float delta = get_delta_t();
    struct sensor_data *data = get_sensors();
    struct computed_state *state = new struct computed_state;
    
    /* x and y are based on integration of the accelerometer data
       z still is, but we should switch it to being based on the pressure */
    state->a_x = data->a_x;
    state->a_y = data->a_y;
    state->a_z = data->a_z;
    state->v_x += state->a_x * delta;
    state->v_y += state->a_y * delta;
    state->v_z += state->a_z * delta;
    state->x += state->v_x * delta;
    state->y += state->v_y * delta;
    state->z += state->v_z * delta;

    /* angular positions are based on integration, but angular acceleration is
       based on deriving the angular velocities */
    state->v_yaw = data->v_yaw;
    state->v_pitch = data->v_pitch;
    state->v_roll = data->v_roll;
    state->yaw += state->v_yaw * delta;
    state->pitch += state->v_pitch * delta;
    state->roll += state->v_roll * delta; 
    state->a_yaw = (state->v_yaw - prev_state->v_yaw) / delta;
    state->a_pitch = (state->v_pitch - prev_state->v_pitch) / delta;
    state->a_roll = (state->v_roll - prev_state->v_roll) / delta;
    
    
    state->pressure = data->pressure;

    delete data;
    if(prev_state != NULL) delete prev_state;
    prev_state = state;
    return state;
}