#include "blocks.h"
#include <assert.h>
#include <string.h>
#include "canvas.h"

const uint8_t block_hollow_pix[] = { 7, 5, 7 };
const uint8_t block_filled_pix[] = { 7, 7, 7 };
const uint8_t empty[] = { 0, 0, 0 };

const canvas_t block_empty = {
    .w = 3, .h = 3, .data = (uint8_t*) block_hollow_pix
};

const canvas_t block_filled = {
    .w = 3, .h = 3, .data = (uint8_t*) block_filled_pix
};

const canvas_t nothing = {
    .w = 3, .h = 3, .data = (uint8_t*) empty
};

const uint8_t shapes[] = {
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,

    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,
    
    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    0, 0, 0, 0,
    1, 1, 1, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,

    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,
};

static void rotate(const uint8_t *shape, uint8_t rot, uint8_t *shape_rot) {
    rot %= 4;
    memcpy(shape_rot, shape, 16);
}

void brick_draw(uint8_t shape, uint8_t rotation, canvas_t *cv, uint8_t fx, uint8_t fy) {
    assert(shape < sizeof(shapes) / 16);
    const uint8_t *pshape = &shapes[shape*16];
    uint8_t shape_rotated[16];
    rotate(pshape, rotation, shape_rotated);
    int x, y;
    for( y = 0; y < 4; y++ ) {
        for( x = 0; x < 4; x++ ) {
            if( shape_rotated[x+y*4]) {
                canvas_blit(&block_filled, cv, (fx + x) * block_filled.w, (fy + y) * block_filled.h);
            } else {
                canvas_blit(&nothing, cv, (fx + x) * block_filled.w, (fy + y) * block_filled.h);
            }
        }
    }
}
