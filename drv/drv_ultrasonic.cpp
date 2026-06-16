#include "drv_ultrasonic.h"

sonar_status_t drv_ultrasonic_init(void) {
    return SONAR_OK;
}

drv_ultrasonic_result_t drv_ultrasonic_measure(void) {
    drv_ultrasonic_result_t result = { SONAR_ERR_GENERIC, 0 };

    /* Drive SIG pin to send trigger pulse */
    hal_pin_mode(HAL_PIN_ULTRASONIC, hal_pin_dir_t::DIR_OUTPUT);
    hal_pin_write(HAL_PIN_ULTRASONIC, hal_pin_level_t::LVL_LOW);
    hal_delay_us(2);
    hal_pin_write(HAL_PIN_ULTRASONIC, hal_pin_level_t::LVL_HIGH);
    hal_delay_us(SONAR_TRIGGER_US);
    hal_pin_write(HAL_PIN_ULTRASONIC, hal_pin_level_t::LVL_LOW);

    /* Switch SIG pin to input to receive echo */
    hal_pin_mode(HAL_PIN_ULTRASONIC, hal_pin_dir_t::DIR_INPUT);

    /* Measure echo and convert to distance: dist_cm = duration_us * 17 / 1000
       derived from: distance = duration * 340 m/s / 2, units µs → cm */
    hal_pulse_result_t pulse = hal_pulse_in(
        HAL_PIN_ULTRASONIC, hal_pin_level_t::LVL_HIGH, SONAR_ECHO_TIMEOUT_US);

    if (pulse.status == SONAR_ERR_TIMEOUT) {
        result.status = SONAR_ERR_TIMEOUT;
    } else {
        uint16_t dist = (uint16_t)(pulse.duration_us * 17u / 1000u);
        if (dist < SONAR_MIN_RANGE_CM || dist > SONAR_MAX_RANGE_CM) {
            result.status = SONAR_ERR_OUT_OF_RANGE;
        } else {
            result.status  = SONAR_OK;
            result.dist_cm = dist;
        }
    }

    return result;
}
