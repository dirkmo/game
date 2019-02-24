#include "dem128064a.h"
#include "ports.h"

typedef enum {
    DEM_IR = 0,
    DEM_DR = 1
} dem_reg_t;

typedef enum {
    DEM_DISPLAY_OFF = 0x3E, // 62
    DEM_DISPLAY_ON  = 0x3F, // 63
    DEM_SETADDR_X   = 0xB8, // 184
    DEM_SETADDR_Y   = 0x40, // 64
    DEM_SETADDR_Z   = 0xC0, // 192
} dem_command_t;

typedef enum {
    DEM_STATUS_RESET = 0x10,
    DEM_STATUS_ON    = 0x20,
    DEM_STATUS_BUSY  = 0x80
} dem_status_t;

static void dem_write(dem_cs_t cs, dem_reg_t reg, uint8_t val) {
    port_set_ctrl(DEM_PIN_E, 0);
    //delay(1000);
    port_set_ctrl(DEM_PIN_RW, 0);
    port_set_ctrl(DEM_PIN_CS1, (cs & DEM_CS1) != 0 );
    port_set_ctrl(DEM_PIN_CS2, (cs & DEM_CS2) != 0 );
    port_set_ctrl(DEM_PIN_RS, reg == DEM_DR);
    port_set_data(val);
    //delay(1000);
    port_set_ctrl(DEM_PIN_E, 1);
    //delay(1000);
    port_set_ctrl(DEM_PIN_E, 0);
    //delay(1000);
    port_set_ctrl(DEM_PIN_CS1, 0 );
    port_set_ctrl(DEM_PIN_CS2, 0 );
    port_get_data(&val); // dummy read for setting databus to input
}

static void dem_read(dem_cs_t cs, dem_reg_t reg, uint8_t *val) {
    port_get_data(val); // dummy read for setting databus to input
    port_set_ctrl(DEM_PIN_E, 0);
    //delay(1000);
    port_set_ctrl(DEM_PIN_RW, 1);
    port_set_ctrl(DEM_PIN_CS1, (cs & DEM_CS1) != 0 );
    port_set_ctrl(DEM_PIN_CS2, (cs & DEM_CS2) != 0 );
    port_set_ctrl(DEM_PIN_RS, reg == DEM_DR);

    //delay(1000);
    port_set_ctrl(DEM_PIN_E, 1);
    //delay(1000);
    port_get_data(val); // actual databus reading

    port_set_ctrl(DEM_PIN_E, 0);
    //delay(1000);
    port_set_ctrl(DEM_PIN_CS1, 0 );
    port_set_ctrl(DEM_PIN_CS2, 0 );
}

void dem_set_x(dem_cs_t cs, uint8_t x) {
    dem_write(cs, DEM_IR, DEM_SETADDR_X | (x & 7));
}

void dem_set_y(dem_cs_t cs, uint8_t y) {
    dem_write(cs, DEM_IR, DEM_SETADDR_Y | (y & 63));
}

void dem_set_z(dem_cs_t cs, uint8_t z) {
    dem_write(cs, DEM_IR, DEM_SETADDR_Z | (z & 63));
}

void dem_fill(uint8_t val) {
    uint8_t x, y;
    dem_set_y(DEM_CS_BOTH, 0);
    for( x = 0; x < 8; x++ ) {
        dem_set_x(DEM_CS_BOTH, x);
        for( y = 0; y < 64; y++ ) {
            dem_write(DEM_CS_BOTH, DEM_DR, val);
        }
    }
}

void dem_copy_raw(const uint8_t *raw) {
    uint8_t x, y;
    dem_set_y(DEM_CS_BOTH, 0);
    for( x = 0; x < 8; x++ ) {
        dem_set_x(DEM_CS_BOTH, x);
        for( y = 0; y < 64; y++ ) {
            uint8_t val1 = raw[y + x*128];
            uint8_t val2 = raw[y+64 + x*128];
            if( val1 == val2 ) {
                dem_write(DEM_CS_BOTH, DEM_DR, val1);
            } else {
                dem_write(DEM_CS1, DEM_DR, val1);
                dem_write(DEM_CS2, DEM_DR, val2);
            }
        }
    }
}

void dem_copy(const uint8_t *fb) {
    uint8_t x, y, b;
    dem_set_y(DEM_CS_BOTH, 0);
    for( x = 0; x < 8; x++ ) {
        dem_set_x(DEM_CS_BOTH, x);
        for( y = 0; y < 64; y++ ) {
            uint8_t val1 = 0, val2 = 0;
            for( b = 0; b < 8; b++ ) {
                val1 |= fb[y + (x+b)*128] << b;
                val2 |= fb[y + 64 + (x+b)*128] << b;
            }
            if( val1 == val2 ) {
                dem_write(DEM_CS_BOTH, DEM_DR, val1);
            } else {
                dem_write(DEM_CS1, DEM_DR, val1);
                dem_write(DEM_CS2, DEM_DR, val2);
            }
        }
    }
}

void dem_enable(void) {
    while(dem_is_busy());
    dem_write(DEM_CS_BOTH, DEM_IR, DEM_DISPLAY_ON );
    while(dem_is_busy());
}

void dem_disable(void) {
    dem_write(DEM_CS_BOTH, DEM_IR, DEM_DISPLAY_OFF );
}

bool dem_is_busy(void) {
    uint8_t status;
    bool busy = false;
    dem_read(DEM_CS1, DEM_IR, &status);
    busy |= (status & DEM_STATUS_BUSY) != 0;
    if( !busy ) {
        dem_read(DEM_CS2, DEM_IR, &status);
        busy |= (status & DEM_STATUS_BUSY) != 0;
    }
    return busy;
}
