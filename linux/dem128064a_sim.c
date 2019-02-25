#include "dem128064a_sim.h"

typedef enum {
    DEM_CMD_DISPLAY_OFF = 0x3E,
    DEM_CMD_DISPLAY_ON  = 0x3F,
    DEM_CMD_SETADDR_X   = 0xB8,
    DEM_CMD_SETADDR_Y   = 0x40,
    DEM_CMD_SETADDR_Z   = 0xC0,
} DEM_CMD;

typedef struct {
    uint8_t ram[64];
    uint8_t x : 3; // page 0..7 (byte address)
    uint8_t y : 6; // line (0..63), auto increment
    uint8_t z : 6; // start line (0..63)
    uint8_t reset;
    uint8_t on;
    uint8_t busy;
} display_t;

static display_t disp1;
static display_t disp2;

//------------------------------------------------------------------------------

static void dem_cmd( display_t *disp, uint8_t cmd ) {
    if( (cmd & DEM_CMD_DISPLAY_OFF) == DEM_CMD_DISPLAY_OFF) {
        disp->on = cmd & 1;
    } else if( (cmd & DEM_CMD_SETADDR_X) == DEM_CMD_SETADDR_X ) {
        disp->x = cmd & 0x3F;
    } else if( (cmd & DEM_CMD_SETADDR_Y) == DEM_CMD_SETADDR_Y ) {
        disp->y = cmd & 0x07;
    } else if( (cmd & DEM_CMD_SETADDR_Z) == DEM_CMD_SETADDR_Z ) {
        disp->z = cmd & 0x3F;
    }
}

static void dem_write( display_t *disp, uint8_t rs, uint8_t dat ) {
    if( rs == 0 ) {
        // instruction
        dem_cmd( disp, dat );
    } else {
        // data
        uint8_t addr = disp->y + disp->x * 8;
        disp->ram[addr] = dat;
        disp->y++;
    }
}

static void dem_read( display_t *disp, uint8_t rs, uint8_t *dat ) {
    if( rs == 0 ) {
        // read status
        *dat = (disp->busy << 7) | (disp->on << 5) | (disp->reset << 4);
    } else {
        // read ram data, need a dummy read for accessing
        static uint8_t datalatch = 0;
        uint8_t addr = disp->y + disp->x * 8;
        *dat = datalatch;
        datalatch = disp->ram[addr];
        disp->y++;
    }
}

void dem_bus( uint8_t rw, uint8_t rs, uint8_t e, uint8_t cs, uint8_t *dat ) {
    static uint8_t e_old = 0;
    if( e_old != e ) {
        e_old = e;
        // enable pin rising edge
        if( rw == 0 ) {
            // write access
            if( cs & 1 ) {
                dem_write( &disp1, rs, *dat );
            }
            if( cs & 2 ) {
                dem_write( &disp2, rs, *dat );
            }
        }
    }
    if( e && rw ) {
        if( cs & 1 ) {
            dem_read( &disp1, rs, dat);
        }
        if( cs & 2 ) {
            dem_read( &disp2, rs, dat);
        }
    }
}
