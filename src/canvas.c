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
            uint8_t byte = src->data[i + (srcy/8)*src->w];
            blitbyte( byte, len, dst, x + i, y + srcy );
        }
    }
    
}

void canvas_hline( canvas_t *dst, uint32_t x1, uint32_t x2, uint32_t y, bool val) {
    const int dsty = y / 8;
    const int offset = y % 8;
    const uint8_t mask = 1 << offset;
    if( x1 >= dst->w ) {
        x1 = dst->w-1;
    }
    if( x2 >= dst->w ) {
        x2 = dst->w-1;
    }
    if( x1 > x2 ) {
        uint32_t t = x1;
        x1 = x2;
        x2 = t;
    }
    if( y < dst->h ) {
        for( uint32_t x = x1; x <= x2; x++ ) {
            const int addr = x + dsty*dst->w;
            if ( val ) {
                dst->data[addr] |= mask;
            } else {
                dst->data[addr] &= ~mask;
            }
        }
    }
}

void canvas_vline( canvas_t *dst, uint32_t x, uint32_t y1, uint32_t y2, bool val) {
    if(y1 < dst->h && y2 < dst->h && x < dst->w) {
        if( y2 < y1 ) {
            uint32_t t = y1;
            y1 = y2;
            y2 = t;
        }
        uint32_t dsty1 = y1 / 8;
        uint32_t dsty2 = y2 / 8;
        int mask1 = 0xFFu << (y1 % 8);
        int mask2 = 0xFFu >> (8 - (y2 % 8));

        for( uint32_t y = dsty1; y <= dsty2; y++ ) {
            int mask = 0xFF;
            if( y == dsty1 ) {
                mask = mask1;
            }
            if( y == dsty2 ) {
                mask = mask1 & mask2;
            }
            if( val ) {
                dst->data[x + y * dst->w] |= mask;
            } else {
                dst->data[x + y * dst->w] &= ~mask;
            }   
        }
    }
}

void canvas_putpixel( canvas_t *dst, uint32_t x, uint32_t y, bool val ) {
    if( x < dst->w && y < dst->h ) {
        const int dsty = y / 8;
        const int offset = y % 8;
        const uint8_t mask = 1 << offset;
        const int addr = x + dsty*dst->w;
        if (val) {
            dst->data[addr] |= mask;
        } else {
            dst->data[addr] &= ~mask;
        }
    }
}
