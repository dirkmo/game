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


static void blitbyte( uint8_t byte, uint8_t len, canvas_t *dst, uint32_t x, uint32_t y) {
    uint8_t src_mask = 0xFFu >> (8-len);
    byte &= src_mask;
    int dst_h_off = y % 8; // offset
    uint32_t d1_addr = x + (y/8) * dst->w;
    uint8_t *d1 = &dst->data[d1_addr];
    int d1_count = 8 - dst_h_off; // how many pixels fit into d1 with regards to offset
    uint8_t d1_mask = 0xFFu << dst_h_off;
    *d1 &= ~d1_mask;
    *d1 |= byte << dst_h_off;

    if( d1_count < len ) {
        uint32_t d2_addr = x + (y/8+1) * dst->w;
        uint8_t *d2 = &dst->data[d2_addr];
        int d2_count = len - d1_count;
        uint8_t d2_mask = 0xFFu >> (8-d2_count);
        *d2 &= ~d2_mask;
        *d2 |= byte >> d1_count;
    }
}

void canvas_blit( const canvas_t *src, canvas_t *dst, uint32_t x, uint32_t y ) {
    for( int srcy = 0; srcy < src->h; srcy+=8 ) {
        for( int i = 0; i < src->w; i++ ) {
            int len = src->h - srcy;
            if( len > 8 ) {
                len = 8;
            }
            blitbyte( src->data[i + (srcy/8)*src->w], len, dst, x + i, y + srcy );
        }
    }
    
}
