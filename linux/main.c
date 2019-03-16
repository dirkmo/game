#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL.h>
#include "dem128064a_sim.h"
#include "game.h"

static SDL_TimerID timer;
static int scale = 6;

static uint32_t timer_callback( uint32_t interval, void *param) {
    game_timer_callback();
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

void handle_keyboard(SDL_Event *event) {
    static uint32_t buttons = 0;
    uint32_t mask;
    bool pressed = (event->type == SDL_KEYDOWN);
    switch( event->key.keysym.sym ) {
        case SDLK_LEFT:  mask = BUTTON_LEFT; break;
        case SDLK_RIGHT: mask = BUTTON_RIGHT; break;
        case SDLK_UP:    mask = BUTTON_UP; break;
        case SDLK_DOWN:  mask = BUTTON_DOWN; break;
        case SDLK_y:     mask = BUTTON_ACTION0; break;
        case SDLK_x:     mask = BUTTON_ACTION1; break;
        case SDLK_c:     mask = BUTTON_ACTION2; break;
        case SDLK_v:     mask = BUTTON_ACTION3; break;
        default: return;
    }
    if( pressed ) {
        buttons |= mask;
    } else {
        buttons &= ~mask;
    }
    game_button_callback(buttons);
}

int main(int argc, char *argv[]) {
    parseParameters(argc, argv);

    timer = SDL_AddTimer( GAME_TIMER_MS, timer_callback, NULL );

    sdl_setup(scale);
    
    game_init();
    while(1) {
        game_loop();
        dem_update_screen();
        SDL_Event event;
        if( SDL_PollEvent(&event) ) {
            if( event.type == SDL_QUIT ) {
                break;
            } else if( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                handle_keyboard(&event);
            }
        }
    }
    SDL_RemoveTimer(timer);

    sdl_close();
}
