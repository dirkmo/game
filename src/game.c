#include <stdio.h>

#include "game.h"
#include "dem128064a.h"
#include "salma.h"

void game_init(void) {
    printf("Game machine started.\n");
    dem_enable();
    dem_copy_raw(pic_raw);
}

void game_loop(void) {
    
}
