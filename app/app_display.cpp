#include "app_display.h"
#include "../drv/drv_oled.h"
#include "../drv/drv_serial.h"

static bool s_use_serial = false;

sonar_status_t app_display_init(void) {
    sonar_status_t status = SONAR_ERR_GENERIC;
    if (drv_oled_init() == SONAR_OK) {
        status = SONAR_OK;
    } else if (drv_serial_init() == SONAR_OK) {
        s_use_serial = true;
        status = SONAR_OK;
    }
    return status;
}

void app_display_update(drv_ultrasonic_result_t result) {
    if (s_use_serial) {
        if (result.status == SONAR_OK) drv_serial_show_distance(result.dist_cm);
        else                           drv_serial_show_error(result.status);
    } else {
        if (result.status == SONAR_OK) drv_oled_show_distance(result.dist_cm);
        else                           drv_oled_show_error(result.status);
    }
}
