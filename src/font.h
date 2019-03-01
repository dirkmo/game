#ifndef _FONT_H
#define _FONT_H

#include <stdint.h>

void font_put_raw(const uint8_t *font, char c, uint8_t *pos_raw, uint8_t bitoffset);
void font_puts_raw(const uint8_t *font, const char *s, uint8_t *pos_raw, uint8_t bitoffset);

#endif
