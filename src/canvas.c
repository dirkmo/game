#include "canvas.h"
#include <stdio.h>

void printbits(uint8_t val) {
    for( int i = 7; i>=0; i-- ) {
        printf("%d", (val>>i)&1);
    }
    printf("\n");
}

uint32_t canvas_bytesize(const canvas_t *c) {
    uint32_t size = ( c->h / 8 + (c->h % 8 > 0) )* c->w;
    return size;
}


static void blitbyte( const uint8_t byte, uint8_t len, canvas_t *dst, uint32_t x, uint32_t y) {
    uint8_t mask = 0xFFu >> (8-len);

    printbits(mask);
}

void canvas_blit( const canvas_t *src, canvas_t *dst, uint32_t x, uint32_t y ) {
    int h_off = y % 8; // offset

    for( int srcy = 0; srcy < src->h; srcy+=8 ) {
        for( int i = 0; i < 1/*src->w*/; i++ ) {
            int len = src->h - srcy;
            if( len > 8 ) {
                len = 8;
            }
            blitbyte( src->data[i + (srcy/8)*src->w], len, dst, x + i, y + srcy );
        }
    }
    
}
