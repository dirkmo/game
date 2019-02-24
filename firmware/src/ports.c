#include <stdio.h>
#include "ports.h"
#include "system/ports/sys_ports.h"

// Chipkit pins
// Data bus
// 78: RG1 0
// 79: RG0 1
// 80: RA6 2
// 81: RA7 3
// 82: RG14 4
// 83: RG12 5
// 84: RG13 6
// 13: RA3 7
// control signals
//  8: RD12 E
//  9: RD3  RS
// 10: RD4  CS1
// 11: RC4  CS2
// 12: RA2  RW

typedef struct {
    PORTS_CHANNEL ch;
    int idx;
} pin_t;

const pin_t databus[8] = {
    { PORT_CHANNEL_G, 1 },
    { PORT_CHANNEL_G, 0 },
    { PORT_CHANNEL_A, 6 },
    { PORT_CHANNEL_A, 7 },
    { PORT_CHANNEL_G, 14 },
    { PORT_CHANNEL_G, 12 },
    { PORT_CHANNEL_A, 3 },
    { PORT_CHANNEL_G, 13 },
};

const pin_t ctrl[] = {
    { PORT_CHANNEL_D, 12 }, // DEM_PIN_E
    { PORT_CHANNEL_D,  3 }, // DEM_PIN_RS
    { PORT_CHANNEL_D,  4 }, // DEM_PIN_CS1
    { PORT_CHANNEL_C,  4 }, // DEM_PIN_CS2
    { PORT_CHANNEL_A,  2 }, // DEM_PIN_RW
    { PORT_CHANNEL_D,  7 }, // DEM_PIN_RSTB
};

void port_set_data(uint8_t val) {
    int i;
    for( i=0; i<8; i++) {
        SYS_PORTS_PinDirectionSelect(
            PORTS_ID_0, SYS_PORTS_DIRECTION_OUTPUT,
            databus[i].ch, databus[i].idx
        );
        SYS_PORTS_PinWrite(
            PORTS_ID_0,
            databus[i].ch, databus[i].idx,
            (val >> i) & 1
        );
    }
}

void port_get_data(uint8_t *val) {
    int i;
    *val = 0;
    for( i=0; i<8; i++) {
        SYS_PORTS_PinDirectionSelect(
            PORTS_ID_0, SYS_PORTS_DIRECTION_INPUT,
            databus[i].ch, databus[i].idx
        );
        bool v = SYS_PORTS_PinRead(
            PORTS_ID_0,
            databus[i].ch, databus[i].idx
        );
        *val |= v << i;
    }
}

void port_set_ctrl(dem_pins_t pin_idx, int val) {
    SYS_PORTS_PinDirectionSelect(
        PORTS_ID_0, SYS_PORTS_DIRECTION_OUTPUT,
        ctrl[pin_idx].ch, ctrl[pin_idx].idx
    );
    SYS_PORTS_PinWrite(
        PORTS_ID_0,
        ctrl[pin_idx].ch, ctrl[pin_idx].idx,
        val & 1
    );
}
