#include <stdio.h>
#include <string.h>

#include "game.h"
#include "dem128064a.h"
#include "salma.h"
#include "font.h"
#include "font_6x8.h"
#include "canvas.h"
#include "blocks.h"
#include "buttons.h"

static uint8_t fbuf[128*8];
static uint8_t bgbuf[128*8];

static canvas_t screen = {
    .w = 128,
    .h = 64,
    .data = fbuf
};

static canvas_t background = {
    .w = 128,
    .h = 64,
    .data = bgbuf
};

static uint8_t s_rotation;

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

void game_loop(void) {
    if( button_pressed(BUTTON_ACTION0) ) {
        s_rotation = (s_rotation + 1) % 4;
    }
}

