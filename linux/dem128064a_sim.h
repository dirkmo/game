#ifndef _DEM128064A_SIM_H
#define _DEM128064A_SIM_H

#include <stdint.h>

void dem_bus( uint8_t rw, uint8_t rs, uint8_t e, uint8_t cs, uint8_t *dat );

#endif
