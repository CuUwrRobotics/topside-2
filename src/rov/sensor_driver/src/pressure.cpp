#include <linux/i2c-dev.h>
#include <ePressure.h>

const uint8_t ePressure::ePressureAddress = 0x76;
const uint8_t ePressure::ePressureBus = 6;
const uint8_t ADC_READ = 0x00;
const uint8_t PROM_READ = 0xA0;
const uint8_t CONVERT = 0x4A;

const float Pa = 100.0f;
const int fluidDensity = 1025; // kg/m^3

bool ePressure::init() {
    char filename[32];
    snprintf(filename, sizeof(filename), "/dev/i2c-%d", bus);

    int fd = open(filename, O_RDWR);
    if (fd < 0) {
        std::cerr << "Failed to open the I2C bus" << std::endl;
        return false;
    }

    if (ioctl(fd, I2C_SLAVE, address) < 0) {
        std::cerr << "Failed to acquire bus access and/or talk to slave" << std::endl;
        close(fd);
        return false;
    }

    // Reset sensor
    uint8_t reset_cmd = MS5837_RESET;
    if (write(fd, &reset_cmd, 1) != 1) {
        std::cerr << "Failed to reset the sensor" << std::endl;
        close(fd);
        return false;
    }
    usleep(10000); // 10ms delay for reset completion

    for (uint8_t i = 0; i < 7; i++) {
        uint8_t prom_cmd = MS5837_PROM_READ + (i * 2);
        if (write(fd, &prom_cmd, 1) != 1) {
            std::cerr << "Failed to send PROM read command" << std::endl;
            close(fd);
            return false;
        }

        uint8_t buffer[2];
        if (read(fd, buffer, 2) != 2) {
            std::cerr << "Failed to read PROM data" << std::endl;
            close(fd);
            return false;
        }
        C[i] = (buffer[0] << 8) | buffer[1];
    }

    close(fd);
    return true;
}
void ePressure::read() {
    char filename[32];
    snprintf(filename, sizeof(filename), "/dev/i2c-%d", bus);

    int fd = open(filename, O_RDWR);
    if (fd < 0) {
        std::cerr << "Failed to open the I2C bus" << std::endl;
        return;
    }

    // Request D1 conversion (pressure)
    uint8_t cmd = MS5837_CONVERT_D1_8192;
    if (write(fd, &cmd, 1) != 1) {
        std::cerr << "Failed to request D1 conversion" << std::endl;
        close(fd);
        return;
    }

    usleep(20000); // 20ms delay per datasheet

    cmd = MS5837_ADC_READ;
    if (write(fd, &cmd, 1) != 1) {
        std::cerr << "Failed to request ADC read" << std::endl;
        close(fd);
        return;
    }

    uint8_t buffer[3];
    if (read(fd, buffer, 3) != 3) {
        std::cerr << "Failed to read pressure data" << std::endl;
        close(fd);
        return;
    }

    D1_pres = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
    close(fd);
    calculate();
}

float ePressure::get_ePressure(){
    read();
    int32_t dT = D2_temp - uint32_t(C[5]) * 256l;
    int64_t SENS = int64_t(C[1]) * 65536l + (int64_t(C[3]) * dT) / 128l;
    int64_t OFF = int64_t(C[2]) * 131072l + (int64_t(C[4]) * dT) / 64l;
    P = (D1_pres * SENS / 2097152l - OFF) / 32768l;
    float pressure = P / Pa; // Convert to hPa
    return pressure;
}

int main(){
    ePressure sensor;
    if (!sensor.init()) {
        std::cerr << "Failed to initialize the sensor" << std::endl;
        return -1;
    }
    while(true){
        float pressure = sensor.get_ePressure();
        std::cout << "Pressure: " << pressure << " hPa" << std::endl;
        usleep(1000000); // Sleep for 1 second
    }
    return 0;
}