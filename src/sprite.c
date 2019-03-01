#include "sprite.h"


void blit( const sprite_t *sprite, uint8_t idx, uint8_t *fb, uint8_t x, uint8_t y ) {
    uint8_t w = sprite->w;
    uint8_t h = sprite->h;
    // framesize in bytes
    int bytesize = w * ( h / 8 + (h % 8 > 0) );
    // sprite data to blit at base
    const uint8_t *base = sprite->data + bytesize*idx;

    uint8_t hbits_drawn = 0;
    // draw first part to reach byte boundary
    if( y % 8 ) {
        hbits_drawn = 8 - y % 8;
        int mask = 0xFFu << (y%8);
        if( hbits_drawn > h ) {
            mask &= 0xFFu >> (hbits_drawn-h);
            hbits_drawn = h;
        }
        for(int i = 0; i < w; i++ ) {
            int a = x + (y/8)*128 + i;
            fb[a] &= ~mask;
            //fb[a] |= base[i] << (8-y%8);
        }
    }
}
