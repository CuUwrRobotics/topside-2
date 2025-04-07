#include <bindings.h>


int main(){
    init();
    pwm_enable(true);
    while(true){
        set_pwm_channel_value(CH1, 100); // set pwm
    }

    return 0; 
}

