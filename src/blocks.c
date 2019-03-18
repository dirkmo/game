#include "blocks.h"
#include <assert.h>
#include <string.h>
#include "canvas.h"

const uint8_t block_hollow_pix[] = { 7, 5, 7 };
const uint8_t block_solid_pix[] = { 7, 7, 7 };
const uint8_t empty[] = { 0, 0, 0 };

const canvas_t block_hollow = {
    .w = 3, .h = 3, .data = (uint8_t*) block_hollow_pix
};

const canvas_t block_solid = {
    .w = 3, .h = 3, .data = (uint8_t*) block_solid_pix
};

const canvas_t nothing = {
    .w = 3, .h = 3, .data = (uint8_t*) empty
};

const uint8_t shapes[] = {
    // xxx
    //  x
    0b0000,
    0b1110,
    0b0100,
    0b0000,

    0b0100,
    0b1100,
    0b0100,
    0b0000,
    
    0b0100,
    0b1110,
    0b0000,
    0b0000,

    0b0100,
    0b0110,
    0b0100,
    0b0000,

    // xxxxx
    0b0100,
    0b0100,
    0b0100,
    0b0100,

    0b0000,
    0b1111,
    0b0000,
    0b0000,

    0b0100,
    0b0100,
    0b0100,
    0b0100,

    0b0000,
    0b1111,
    0b0000,
    0b0000,

    // xx
    // xx
    0b0000,
    0b0110,
    0b0110,
    0b0000,

    0b0000,
    0b0110,
    0b0110,
    0b0000,

    0b0000,
    0b0110,
    0b0110,
    0b0000,

    0b0000,
    0b0110,
    0b0110,
    0b0000,

    // x
    // xx
    //  x
    0b0100,
    0b0110,
    0b0010,
    0b0000,

    0b0000,
    0b0011,
    0b0110,
    0b0000,

    0b0100,
    0b0110,
    0b0010,
    0b0000,

    0b0000,
    0b0011,
    0b0110,
    0b0000,
    
    //  x
    // xx
    // x
    0b0010,
    0b0110,
    0b0100,
    0b0000,

    0b0000,
    0b0110,
    0b0011,
    0b0000,

    0b0010,
    0b0110,
    0b0100,
    0b0000,

    0b0000,
    0b0110,
    0b0011,
    0b0000,

    // xxx
    // x
    0b0000,
    0b1110,
    0b1000,
    0b0000,

    0b1100,
    0b0100,
    0b0100,
    0b0000,

    0b0010,
    0b1110,
    0b0000,
    0b0000,

    0b0100,
    0b0100,
    0b0110,
    0b0000,

    // x
    // xxx
    0b1000,
    0b1110,
    0b0000,
    0b0000,

    0b0110,
    0b0100,
    0b0100,
    0b0000,

    0b0000,
    0b1110,
    0b0010,
    0b0000,

    0b0100,
    0b0100,
    0b1100,
    0b0000,
};

bool brick_getblock(uint8_t shape, uint8_t rotation, uint8_t x, uint8_t y ) {
    assert(x < 4 && y < 4);
    const uint8_t *pshape = &shapes[shape*16 + 4*(rotation%4)];
    return (pshape[y] >> (3-x)) & 1;
}

void brick_draw(uint8_t shape, uint8_t rotation, canvas_t *cv, uint8_t fx, uint8_t fy) {
    int x, y;
    for( y = 0; y < 4; y++ ) {
        for( x = 0; x < 4; x++ ) {
            const canvas_t *block_cv = brick_getblock(shape, rotation, x, y) ? &block_solid : &nothing;
            canvas_blit(block_cv, cv, (fx + x) * block_solid.w, (fy + y) * block_solid.h);
        }
    }
}

void block_draw(uint8_t type, canvas_t *cv, uint8_t x, uint8_t y) {
    const canvas_t *blocktypes[] = { &nothing, &block_hollow, &block_solid };
    canvas_blit( blocktypes[type], cv, x*blocktypes[type]->w, y*blocktypes[type]->h );
}

