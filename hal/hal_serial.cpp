#include "hal_serial.h"
#include <Arduino.h>

sonar_status_t hal_serial_init(uint32_t baud) {
    Serial.begin(baud);
    return SONAR_OK;
}

void hal_serial_println(const char *str) {
    Serial.println(str);
}
