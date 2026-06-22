#include "src/app/app_sonar.h"
#include "src/app/app_display.h"
#include "src/hal/hal_gpio.h"

void setup() {
    app_display_init();
}

void loop() {
    app_display_update(app_sonar_tick());
    hal_delay_ms(SONAR_SAMPLE_INTERVAL_MS);
}
