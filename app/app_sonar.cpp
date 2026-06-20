#include "app_sonar.h"

drv_ultrasonic_result_t app_sonar_tick(void) {
    return drv_ultrasonic_measure();
}
