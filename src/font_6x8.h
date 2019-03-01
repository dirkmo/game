#ifndef _FONT_H
#define _FONT_H

#include <stdint.h>

void font_put_raw(char c, uint8_t *pos_raw, uint8_t bitoffset);
void font_put(char c, uint8_t *pos_raw);

#endif
