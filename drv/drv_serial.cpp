#include "drv_serial.h"
#include "../hal/hal_serial.h"
#include <stdio.h>

sonar_status_t drv_serial_init(void) {
    return hal_serial_init(9600);
}

void drv_serial_show_distance(uint16_t dist_cm) {
    char buf[32];
    snprintf(buf, sizeof(buf), "Target is %u cm away", dist_cm);
    hal_serial_println(buf);
}

void drv_serial_show_error(sonar_status_t err) {
    if      (err == SONAR_ERR_TIMEOUT)      hal_serial_println("No target detected");
    else if (err == SONAR_ERR_OUT_OF_RANGE) hal_serial_println("Target outside range");
    else                                    hal_serial_println("Error");
}
