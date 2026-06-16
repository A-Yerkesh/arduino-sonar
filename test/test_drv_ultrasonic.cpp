#include <cassert>
#include "mock_hal_gpio.h"
#include "../drv/drv_ultrasonic.h"

static void test_timeout(void) {
    mock_hal_pulse_in(0);
    drv_ultrasonic_result_t r = drv_ultrasonic_measure();
    assert(r.status == SONAR_ERR_TIMEOUT);
}

static void test_below_min_boundary(void) {
    mock_hal_pulse_in(117); /* 117 µs → 1 cm, below SONAR_MIN_RANGE_CM */
    drv_ultrasonic_result_t r = drv_ultrasonic_measure();
    assert(r.status == SONAR_ERR_OUT_OF_RANGE);
}

static void test_min_boundary(void) {
    mock_hal_pulse_in(118); /* 118 µs → 2 cm = SONAR_MIN_RANGE_CM */
    drv_ultrasonic_result_t r = drv_ultrasonic_measure();
    assert(r.status  == SONAR_OK);
    assert(r.dist_cm == 2);
}

static void test_valid_interior(void) {
    mock_hal_pulse_in(1177); /* 1177 µs → 20 cm */
    drv_ultrasonic_result_t r = drv_ultrasonic_measure();
    assert(r.status  == SONAR_OK);
    assert(r.dist_cm == 20);
}

static void test_max_boundary(void) {
    mock_hal_pulse_in(23530); /* 23530 µs → 400 cm = SONAR_MAX_RANGE_CM */
    drv_ultrasonic_result_t r = drv_ultrasonic_measure();
    assert(r.status  == SONAR_OK);
    assert(r.dist_cm == 400);
}

static void test_above_max_boundary(void) {
    mock_hal_pulse_in(23589); /* 23589 µs → 401 cm, above SONAR_MAX_RANGE_CM */
    drv_ultrasonic_result_t r = drv_ultrasonic_measure();
    assert(r.status == SONAR_ERR_OUT_OF_RANGE);
}

int main(void) {
    drv_ultrasonic_init();
    test_timeout();
    test_below_min_boundary();
    test_min_boundary();
    test_valid_interior();
    test_max_boundary();
    test_above_max_boundary();
    return 0;
}
