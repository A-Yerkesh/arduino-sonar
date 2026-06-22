/**
 * drv_serial.h — Serial output driver interface.
 *
 * Fallback output when the OLED is unavailable. Depends on hal_serial.
 */

#ifndef DRV_SERIAL_H
#define DRV_SERIAL_H

#include "../globals.h"

sonar_status_t drv_serial_init(void);
void drv_serial_show_distance(uint16_t dist_cm);
void drv_serial_show_error(sonar_status_t err);

#endif /* DRV_SERIAL_H */
