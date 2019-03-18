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

#define FIELD_W 12
#define FIELD_H (64 / 3)
// left border
#define FIELD_L (128/6 - FIELD_W/2)
// right border
#define FIELD_R (128/6 + FIELD_W/2)

static uint32_t s_tick;

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

static uint8_t field[FIELD_W*FIELD_H];

static struct brick_t {
    uint8_t rotation;
    uint8_t shape;
    int x;
    int y;
} brick;

void background_from_field(void) {
    memset(field, 2, sizeof(field));
    int x, y;
    for( y = 0; y < FIELD_H; y++ ) {
        for( x = 0; x < FIELD_W; x++ ) {
            block_draw(field[x+y*FIELD_W], &background, FIELD_L+x, y);
	}
    }
}

bool collision( int x, int y ) {
    return false;
}

void move(int _x, int _y) {
    int x = brick.x + _x;
    int y = brick.y + _y;
    if( !collision(x, y) ) {
        brick.x = x;
        brick.y = y;
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

    brick.x = 0;
    brick.y = 0;
    brick_draw(brick.shape, brick.rotation, &screen, brick.x, brick.y);

    dem_copy_raw(screen.data);
}

void game_timer_callback(void) {
    s_tick++;
}

void game_loop(void) {
    bool draw = false;
    static uint32_t tick = 0xFFFFFFFF;

    if( button_pressed(BUTTON_UP) ) {
        brick.rotation = (brick.rotation + 1) % 4;
        printf("rotation %d\n", brick.rotation);
        draw = true;
    }

    if( button_pressed(BUTTON_ACTION0) ) {
        brick.shape = (brick.shape + 1) % 7;
        printf("shape %d\n", brick.shape);
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

    if( (tick != s_tick) && (s_tick % 100 == 0) ) {
	tick = s_tick;
        brick.y++;
        if( collision(brick.x, brick.y) ) {
            // kaputt
        }
        draw = true;
    }

    if( draw ) {
        background_from_field();
        canvas_blit(&background, &screen, 0, 0);
        int x = brick.x + FIELD_L;
        int y = brick.y;
        brick_draw(brick.shape, brick.rotation, &screen, x, y);
        dem_copy_raw(screen.data);
        draw = false;
    }
}

