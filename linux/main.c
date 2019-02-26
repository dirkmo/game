#include <stdio.h>
#include <unistd.h>
#include <SDL.h>
#include "dem128064a_sim.h"
#include "game.h"

#define TIMER_MS 50

static SDL_TimerID timer;
static int scale = 7;

static uint32_t timer_callback( uint32_t interval, void *param) {
    return interval;
}

void parseParameters(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "s:")) != -1) {
        switch(opt) {
            case 's':
                scale = atoi(optarg);
                printf("Setting scale to %d\n", scale);
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {
    parseParameters(argc, argv);

    timer = SDL_AddTimer( TIMER_MS, timer_callback, NULL );

    sdl_setup(scale);
    
    game_init();
    while(1) {
        game_loop();
        dem_update_screen();
        SDL_Event event;
        if( SDL_PollEvent(&event) ) {
            if( event.type == SDL_QUIT ) {
                break;
            } else if( event.type == SDL_KEYDOWN ) {
                if( event.key.keysym.sym == SDL_SCANCODE_LEFT ) {
                }
            }
        }
    }
    SDL_RemoveTimer(timer);

    sdl_close();
}
