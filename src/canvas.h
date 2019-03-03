#ifndef _CANVAS_H
#define _CANVAS_H

#include <stdint.h>

typedef struct {
    uint32_t w; // pixel width
    uint32_t h; // pixel height
    uint8_t *data;
} canvas_t;

uint32_t canvas_bytesize(const canvas_t *c);

void canvas_blit( const canvas_t *src, canvas_t *dst, uint32_t x, uint32_t y );

#endif
