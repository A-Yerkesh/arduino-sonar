/**
 * hal_serial.h — Serial output HAL interface.
 *
 * Wraps Arduino Serial for fallback text output when the OLED is unavailable.
 */

#ifndef HAL_SERIAL_H
#define HAL_SERIAL_H

#include "../globals.h"

/**
 * Initialize the UART at the given baud rate.
 *
 * @return SONAR_OK always — Serial.begin() cannot fail on ATmega328P (UART-based).
 */
sonar_status_t hal_serial_init(uint32_t baud);

/**
 * Print a null-terminated string followed by a newline.
 * Failure is not detectable: Serial does not surface UART write errors.
 */
void hal_serial_println(const char *str);

#endif /* HAL_SERIAL_H */
