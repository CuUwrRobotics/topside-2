#include "bindings.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  printf("Initiating navigator module.\n");
  init();

  printf("Setting led on!\n");
  set_led(UserLed::Led1, true);

  printf("Temperature: %f\n", read_temp());
  printf("Pressure: %f\n", read_pressure());

  ADCData adc = read_adc_all();
  printf("Reading ADC Channels: 1 = %f, 2 = %f, 3 = %f, 4 = %f\n",
         adc.channel[0], adc.channel[1], adc.channel[2], adc.channel[3]);
  printf("Data ADC Channels: 1 = %f\n", read_adc(AdcChannel::Ch1));

  AxisData mag = read_mag();
  printf("Magnetic field: X = %f, Y = %f, Z = %f\n", mag.x, mag.y, mag.z);

  return 0;
}
