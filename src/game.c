#include <stdio.h>

#include "game.h"
#include "dem128064a.h"
#include "salma.h"

void game_init(void) {
    printf("Game machine started.\n");
    dem_enable();
    dem_copy_raw(pic_raw_salma);
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
