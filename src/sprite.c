#include "sprite.h"

void blit( const sprite_t *sprite, uint8_t idx, uint8_t *fb, uint8_t x, uint8_t y ) {
    uint8_t w = sprite->w;
    uint8_t h = sprite->h;
    // framesize in bytes
    int bytesize = w * ( h / 8 + (h % 8 > 0) );
    const uint8_t *base = sprite->data + bytesize*idx;



}
