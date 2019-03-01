#ifndef DEM128064A_H
#define	DEM128064A_H

#include <stdint.h>
#include <stdbool.h>

// x=[0,127], y=[0,63]
#define PUTPIXEL(ptr,x,y,val) if(val) { \
        ptr[x + y/8] |= 1 << (y%8);     \
    } eles {                            \
        ptr[x + y/8] &= ~(1 << (y%8));  \
    }

typedef enum {
    DEM_CS_NONE = 0,
    DEM_CS1     = 1,
    DEM_CS2     = 2,
    DEM_CS_BOTH = 3,
} dem_cs_t;

void dem_set_x(dem_cs_t cs, uint8_t x);
void dem_set_y(dem_cs_t cs, uint8_t y);
void dem_set_z(dem_cs_t cs, uint8_t z);
void dem_fill(uint8_t val);
void dem_copy_raw(const uint8_t *raw);
void dem_copy(const uint8_t *fb);
void dem_enable(void);
void dem_disable(void);
bool dem_is_busy(void);

#endif	/* DEM128064A_H */

