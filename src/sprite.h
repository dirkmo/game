#ifndef _SPRITE_H
#define _SPRITE_H

#include <stdint.h>

typedef struct {
    uint8_t *data; // ptr to frame pixel data
    uint8_t w; // width
    uint8_t h; // height
    uint8_t frame_num; // total frames
} sprite_t;

void blit( const sprite_t *sprite, uint8_t idx, uint8_t *fb, uint8_t x, uint8_t y );

#endif
