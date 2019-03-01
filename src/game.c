#include <stdio.h>
#include <string.h>

#include "game.h"
#include "dem128064a.h"
#include "salma.h"
#include "font.h"
#include "font_6x8.h"
#include "sprite.h"

static uint8_t fbuf[128*8];

void game_init(void) {
    printf("Game machine started.\n");
    dem_enable();
    //dem_copy_raw(pic_raw_salma);
    memset(fbuf, 0xFF, 128*8);
    font_puts_raw( font_6x8, "Dirk Moeller", fbuf, 1);

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
