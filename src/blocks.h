#ifndef _BLOCKS_H
#define _BLOCKS_H

#include "canvas.h"

// a brick "lives" in a field of 4x4 blocks.
// return true, if (x,y) is filled or free.
bool brick_getblock(uint8_t shape, uint8_t rotation, uint8_t x, uint8_t y );

// draw brick to canvas
void brick_draw(uint8_t shape, uint8_t rotation, canvas_t *cv, uint8_t fx, uint8_t fy);

#endif

