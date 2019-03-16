#include <stdio.h>
#include <string.h>

#include "game.h"
#include "dem128064a.h"
#include "salma.h"
#include "font.h"
#include "font_6x8.h"
#include "canvas.h"
#include "blocks.h"

static uint8_t fbuf[128*8];

canvas_t screen = {
    .w = 128,
    .h = 64,
    .data = fbuf
};

void game_init(void) {
    printf("Game machine started.\n");
    dem_enable();

    memset(screen.data, 0x00, canvas_bytesize(&screen));
    int i;
    for( i = 0; i < screen.h/8; i++ ) {
        canvas_putpixel(&screen, 0, i*8, true);
    }

    // for( i = 0; i < 4; i++ ) {
    //     canvas_vline(&screen, 41+i, 0, 63, true );
    //     canvas_vline(&screen, 41+4 + 12*3 + 4-i, 0, 63, true );
    // }

    brick_draw(0, 0, &screen, 0, 0);

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
