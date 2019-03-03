#include <stdio.h>
#include <string.h>

#include "game.h"
#include "dem128064a.h"
#include "salma.h"
#include "font.h"
#include "font_6x8.h"
#include "canvas.h"

static uint8_t fbuf[128*8];

canvas_t screen = {
    .w = 128,
    .h = 64,
    .data = fbuf
};

uint8_t spritedata[] = {
    0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80,
};

canvas_t sprite = {
    .w = 4, .h = 24,
    .data = spritedata
};

void game_init(void) {
    printf("Game machine started.\n");
    dem_enable();
    //dem_copy_raw(pic_raw_salma);

    memset(screen.data, 0xFF, canvas_bytesize(&screen));
    for( int i = 0; i < screen.h/8; i++ ) {
        screen.data[i*screen.w] = 0xfe;
    }
    canvas_blit( &sprite, &screen, 2, 1);

    dem_copy_raw(screen.data);
}

void game_timer_callback(void) {
    
}

void game_button_callback(uint32_t _buttons) {
    static uint32_t buttons = 0;
    if( buttons != _buttons ) {
        buttons = _buttons;

    }
}

void game_loop(void) {
    
}
