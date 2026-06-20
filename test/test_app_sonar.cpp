#include <cassert>
#include "mock_hal_gpio.h"
#include "../app/app_sonar.h"

static void test_propagates_timeout(void) {
    mock_hal_pulse_in(0);
    drv_ultrasonic_result_t r = app_sonar_tick();
    assert(r.status == SONAR_ERR_TIMEOUT);
}

static void test_propagates_below_min(void) {
    mock_hal_pulse_in(117); /* 117 µs → 1 cm, below SONAR_MIN_RANGE_CM */
    drv_ultrasonic_result_t r = app_sonar_tick();
    assert(r.status == SONAR_ERR_OUT_OF_RANGE);
}

static void test_propagates_min_boundary(void) {
    mock_hal_pulse_in(118); /* 118 µs → 2 cm = SONAR_MIN_RANGE_CM */
    drv_ultrasonic_result_t r = app_sonar_tick();
    assert(r.status  == SONAR_OK);
    assert(r.dist_cm == 2);
}

static void test_propagates_valid(void) {
    mock_hal_pulse_in(1177); /* 1177 µs → 20 cm */
    drv_ultrasonic_result_t r = app_sonar_tick();
    assert(r.status  == SONAR_OK);
    assert(r.dist_cm == 20);
}

static void test_propagates_max_boundary(void) {
    mock_hal_pulse_in(23530); /* 23530 µs → 400 cm = SONAR_MAX_RANGE_CM */
    drv_ultrasonic_result_t r = app_sonar_tick();
    assert(r.status  == SONAR_OK);
    assert(r.dist_cm == 400);
}

static void test_propagates_above_max(void) {
    mock_hal_pulse_in(23589); /* 23589 µs → 401 cm, above SONAR_MAX_RANGE_CM */
    drv_ultrasonic_result_t r = app_sonar_tick();
    assert(r.status == SONAR_ERR_OUT_OF_RANGE);
}

int main(void) {
    test_propagates_timeout();
    test_propagates_below_min();
    test_propagates_min_boundary();
    test_propagates_valid();
    test_propagates_max_boundary();
    test_propagates_above_max();
    return 0;
}
