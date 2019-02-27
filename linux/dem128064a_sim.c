#include "dem128064a_sim.h"
#include <SDL.h>
#include <stdbool.h>

#define SX 128
#define SY 64
#define SPACE 1

typedef enum {
    DEM_CMD_DISPLAY_OFF = 0x00,
    DEM_CMD_DISPLAY_ON  = 0x01,
    DEM_CMD_SETADDR_X   = 0x80,
    DEM_CMD_SETADDR_Y   = 0x40,
    DEM_CMD_SETADDR_Z   = 0xC0,

    DEM_CMD_MASK        = 0xC0
} DEM_CMD;

typedef struct {
    uint8_t ram[64 * 8];
    uint8_t x; // page 0..7 (byte address)
    uint8_t y; // line (0..63), auto increment
    uint8_t z; // start line (0..63)
    uint8_t reset;
    uint8_t on;
    uint8_t busy;
} display_t;

static display_t disp1;
static display_t disp2;

static SDL_Window *win;
static SDL_Surface *screen;
static int scale = 5;

static bool dem_get_pixel( uint8_t y, uint8_t x );

//------------------------------------------------------------------------------

void sdl_setup(int _scale) {
    scale = _scale;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    win = SDL_CreateWindow("Game Machine", 200, 100, SX*scale + (SX+1)*SPACE, SY*scale + (SY+1)*SPACE, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(win);
}

void sdl_close() {
    SDL_DestroyWindow(win);
    SDL_Quit();
}

//------------------------------------------------------------------------------

#if 0
static bool dem_get_pixel( uint8_t _y, uint8_t _x ) {
    uint8_t y = _y;
    uint8_t x = _x / 8;
    uint8_t bit = _x % 8;

    int addr = x*128 + y;
    extern uint8_t pic_raw[];
    return (pic_raw[addr] >> bit) & 1;
}

#else

static bool dem_get_pixel( uint8_t _y, uint8_t _x ) {
    // ---> y axis
    // |
    // v
    // x axis
    display_t *d = _y < 64 ? &disp1 : &disp2;
    uint8_t y = _y % 64;
    uint8_t x = _x / 8;
    uint8_t bit = _x % 8;
    uint16_t addr = x*64 + y;
    return (d->ram[addr] >> bit) & 1;
}
#endif

static void dem_cmd( display_t *disp, uint8_t cmd ) {
    uint8_t cmd_wo_val = cmd & DEM_CMD_MASK;
    switch( cmd_wo_val ) {
        case DEM_CMD_DISPLAY_OFF:
            disp->on = cmd & 1;
            break;
        case DEM_CMD_SETADDR_X:
            disp->x = cmd & 0x07;
            break;
        case DEM_CMD_SETADDR_Y:
            disp->y = cmd & 0x3F;
            break;
        case DEM_CMD_SETADDR_Z:
            disp->z = cmd & 0x3F;
            break;
        default: printf("unknown cmd %02X\n", cmd_wo_val);
    }
}

static void dem_write( display_t *disp, uint8_t rs, uint8_t dat ) {
    if( rs == 0 ) {
        // instruction
        dem_cmd( disp, dat );
    } else {
        // data
        uint16_t addr = disp->y + disp->x * 64;
        disp->ram[addr] = dat;
        disp->y = (disp->y + 1) % 64;
    }
}

static void dem_read( display_t *disp, uint8_t rs, uint8_t *dat ) {
    if( rs == 0 ) {
        // read status
        *dat = (disp->busy << 7) | (disp->on << 5) | (disp->reset << 4);
    } else {
        // read ram data, need a dummy read for accessing
        static uint8_t datalatch = 0;
        uint16_t addr = disp->y + disp->x * 64;
        *dat = datalatch;
        datalatch = disp->ram[addr];
        disp->y = (disp->y + 1) % 64;
    }
}

void dem_bus( uint8_t rw, uint8_t rs, uint8_t e, uint8_t cs, uint8_t *dat ) {
    static uint8_t e_old = 0;
    if( e_old != e ) {
        e_old = e;
        // enable pin rising edge
        if( e && (rw == 0) ) {
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

void dem_update_screen( void ) {
    // funzt
    const uint32_t darkgreen = SDL_MapRGB(screen->format, 0, 50, 0);
    const uint32_t green = SDL_MapRGB(screen->format, 0, 230, 0);
    const uint32_t black = SDL_MapRGB(screen->format, 0, 0, 0);
    SDL_FillRect( screen, NULL, green );
    for( int x = 0; x < 128; x++ ) {
        for( int y = 0; y < 64; y++ ) {
            SDL_Rect rect = { .x = x*scale + (x+1)*SPACE, .y = y*scale + (y+1)*SPACE, .w = scale, .h = scale };
            SDL_FillRect( screen, &rect, dem_get_pixel(x, y) ? black : green );
        }
    }
    SDL_UpdateWindowSurface(win);
}
