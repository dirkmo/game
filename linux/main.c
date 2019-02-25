#include <stdio.h>
#include <SDL.h>
#include "game.h"

static SDL_Window *win;
static SDL_Renderer *ren;

void setup_sdl(void) {
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

}

void close_sdl() {
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    setup_sdl();
    

    game_init();
    while(1) {
        game_loop();
    }
    close_sdl();
}
