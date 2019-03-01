#include <stdio.h>
#include <string.h>

#include "game.h"
#include "dem128064a.h"
#include "salma.h"
#include "font.h"
#include "font_6x8.h"
#include "sprite.h"

static uint8_t fbuf[128*8];

uint8_t spritedata[] = {
    0xf, 0xe, 0x7, 0xf
};

sprite_t sprite = {
    .data = spritedata,
    .w = 4, .h = 4,
    .num = 1
};

void game_init(void) {
    printf("Game machine started.\n");
    dem_enable();
    //dem_copy_raw(pic_raw_salma);

    memset(fbuf, 0xFF, sizeof(fbuf));    
    blit( &sprite, 0, fbuf, 0, 6 );

    dem_copy_raw(fbuf);
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
