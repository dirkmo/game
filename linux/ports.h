#ifndef _PORTS_H_
#define _PORTS_H_

#include <stdint.h>

typedef enum {
    DEM_PIN_E   = 0,
    DEM_PIN_RS  = 1,
    DEM_PIN_CS1 = 2,
    DEM_PIN_CS2 = 3,
    DEM_PIN_RW  = 4,
    DEM_PIN_RSTB = 5,
} dem_pins_t;

void port_set_data(uint8_t val);
void port_get_data(uint8_t *val);
void port_set_ctrl(dem_pins_t pin_idx, int val);

#endif /* _PORTS_H_ */
