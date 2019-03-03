#ifndef _SPRITE_H
#define _SPRITE_H

#include "canvas.h"

typedef struct {
    canvas_t *canvas;
    uint8_t num; // total frames
} sprite_t;

//void blit( const sprite_t *sprite, uint8_t idx, uint8_t *fb, uint8_t x, uint8_t y );

#endif
