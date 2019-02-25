#include <stdio.h>
#include <SDL.h>
#include "game.h"
#include "unistd.h"

#define SX 128
#define SY 64
#define SPACE 2
#define TIMER_MS 50

static SDL_Window *win;
static SDL_Renderer *ren;
static SDL_TimerID timer;
static int scale = 5;

static uint32_t timer_callback( uint32_t interval, void *param) {
    return interval;
}

void setup_sdl(void) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    win = SDL_CreateWindow("Hello World!", 200, 100, SX*scale + (SX+1)*SPACE, SY*scale + (SY+1)*SPACE, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    timer = SDL_AddTimer( TIMER_MS, timer_callback, NULL );
}

void close_sdl() {
    SDL_RemoveTimer(timer);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
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

    setup_sdl();
    
    game_init();
    while(1) {
        game_loop();
        
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

    close_sdl();
}
