#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_DEV "/dev/i2c-6"
#define MS5837_ADDR 0x76
#define MS5837_RESET 0x1E
#define MS5837_ADC_READ 0x00
#define MS5837_PROM_READ 0xA0
#define MS5837_CONVERT_D1_8192 0x4A
#define MS5837_CONVERT_D2_8192 0x5A

int i2c_fd;

void i2c_write_byte(uint8_t cmd) {
    if (write(i2c_fd, &cmd, 1) != 1) {
        perror("I2C Write Error");
        exit(1);
    }
}

void i2c_read_bytes(uint8_t reg, uint8_t *buf, size_t len) {
    if (write(i2c_fd, &reg, 1) != 1) {
        perror("I2C Write (Set Register) Error");
        exit(1);
    }
    if (read(i2c_fd, buf, len) != (ssize_t)len) {
        perror("I2C Read Error");
        exit(1);
    }
}

int main() {
    i2c_fd = open(I2C_DEV, O_RDWR);
    if (i2c_fd < 0) {
        perror("Failed to open I2C device");
        return 1;
    }

    if (ioctl(i2c_fd, I2C_SLAVE, MS5837_ADDR) < 0) {
        perror("Failed to set I2C address");
        return 1;
    }

    i2c_write_byte(MS5837_RESET);
    usleep(10000); // Wait for reset to complete

    uint16_t prom[7];
    for (uint8_t i = 0; i < 7; i++) {
        uint8_t buf[2];
        i2c_read_bytes(MS5837_PROM_READ + (i * 2), buf, 2);
        prom[i] = (buf[0] << 8) | buf[1]; // Combine bytes
        printf("PROM[%d] = %u\n", i, prom[i]);
    }
    while(true){

    i2c_write_byte(MS5837_CONVERT_D1_8192);
    usleep(20000); 
    
    	uint8_t adc_buf[3];
    	i2c_read_bytes(MS5837_ADC_READ, adc_buf, 3);
    	uint32_t D1 = (adc_buf[0] << 16) | (adc_buf[1] << 8) | adc_buf[2];
    	printf("D1 (Pressure Raw) = %u\n", D1);

    }

    close(i2c_fd);
    return 0;
}

