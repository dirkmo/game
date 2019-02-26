#include <stdio.h>

#include "game.h"
#include "dem128064a.h"
#include "salma.h"

void game_init(void) {
    printf("Game machine started.\n");
    dem_enable();
    //dem_copy_raw(pic_raw);
    uint8_t mypic[128 * 8] = { 0 };
    for ( int i = 0; i < 128; i++ ) {
        mypic[i] = 0xFF;
    }
    dem_copy_raw(mypic);
}

void game_loop(void) {
    
}
