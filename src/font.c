#include "font.h"

void font_put_raw(const uint8_t *font, char c, uint8_t *pos_raw, uint8_t bitoffset) {
    const uint8_t *f = &font[(uint8_t)c * 6];
    int upper_mask = 0xFFu << bitoffset;
    int lower_mask = 0xFFu >> (8-bitoffset);
    for( int i = 0; i < 6; i++ ) {
        pos_raw[i] &= ~upper_mask;
        pos_raw[i] |= f[i] << bitoffset;
        // FIXME: potenziell out of bounds!
        pos_raw[i+128] &= ~lower_mask;
        pos_raw[i+128] |= f[i] >> (8-bitoffset);
    }
}

void font_puts_raw(const uint8_t *font, const char *s, uint8_t *pos_raw, uint8_t bitoffset) {
    while( *s ) {
        font_put_raw(font, *s, pos_raw, bitoffset);
        s++;
        pos_raw+=6;
    }
}
