#include <bindings.h>
#include <zmq.hpp>

void bytes_to_pwm(float& coeffs[6]) {
    for (int i = 0; i < 6; i++) {
        coeffs[i] = coeffs[i] * 255;
    }
}
void recieve_coefficients(float& coeffs[6]) {
    zmq::message_t message;
    receiver.recv(&message);
    // break the message into 6 floats
    float* data = (float*)message.data();
    for(int i = 0; i < 6; i++){
        coeffs[i] = data[i];
    }
}
    

int main()
{
    
    // zmq receiver
    zmq::context_t context(1);
    zmq::socket_t receiver(context, ZMQ_PULL);
    receiver.bind("tcp://*:5555");

    float coeffs[6];
    recieve_coefficients(coeffs);
    bytes_to_pwm(coeffs);
    
    return 0;
}
