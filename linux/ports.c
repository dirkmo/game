#include <stdio.h>
#include "ports.h"
#include "dem128064a_sim.h"

static uint8_t ctrl[6] = { 0 };
static uint8_t databus = 0;

void port_set_data(uint8_t val) {
    databus = val;
    uint8_t cs = ctrl[DEM_PIN_CS1] | (ctrl[DEM_PIN_CS2] << 1);
    dem_bus( ctrl[DEM_PIN_RW], ctrl[DEM_PIN_RS], ctrl[DEM_PIN_E], cs, &databus );
}

void port_get_data(uint8_t *val) {
    uint8_t cs = ctrl[DEM_PIN_CS1] | (ctrl[DEM_PIN_CS2] << 1);
    dem_bus( ctrl[DEM_PIN_RW], ctrl[DEM_PIN_RS], ctrl[DEM_PIN_E], cs, &databus );
    *val = databus;
}

void port_set_ctrl(dem_pins_t pin_idx, int val) {
    ctrl[pin_idx] = val ? 1 : 0;
    uint8_t cs = ctrl[DEM_PIN_CS1] | (ctrl[DEM_PIN_CS2] << 1);
    dem_bus( ctrl[DEM_PIN_RW], ctrl[DEM_PIN_RS], ctrl[DEM_PIN_E], cs, &databus );
}
