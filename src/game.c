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

static struct {
    int x;
    int y;
} pos = { .x = 5, .y = 2 };

static uint8_t s_rotation;
static uint8_t s_shape;

bool collision( int x, int y ) {
    return false;
}

void move(int _x, int _y) {
    int x = pos.x + _x;
    int y = pos.y + _y;
    if( !collision(x, y) ) {
        pos.x = x;
        pos.y = y;
    }
}

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

    brick_draw(s_shape, s_rotation, &screen, pos.x, pos.y);

    dem_copy_raw(screen.data);
}

void game_timer_callback(void) {
    
}

void game_loop(void) {
    bool draw = false;
    if( button_pressed(BUTTON_UP) ) {
        s_rotation = (s_rotation + 1) % 4;
        printf("rotation %d\n", s_rotation);
        draw = true;
    }
    if( button_pressed(BUTTON_ACTION0) ) {
        s_shape = (s_shape + 1) % 7;
        printf("shape %d\n", s_shape);
        draw = true;
    }

    if( button_pressed(BUTTON_LEFT) ) {
        move(-1, 0);
        draw = true;
    }

    if( button_pressed(BUTTON_RIGHT) ) {
        move(1, 0);
        draw = true;
    }

    if( draw ) {
        canvas_blit(&background, &screen, 0, 0);
        brick_draw(s_shape, s_rotation, &screen, pos.x, pos.y);
        dem_copy_raw(screen.data);
        draw = false;
    }
}

