#include "font.h"

void font_put_raw(const uint8_t *font, char c, uint8_t *pos_raw, uint8_t bitoffset) {
    const uint8_t *f = &font[(uint8_t)c * 6];
    if( bitoffset == 0 ) {
        for( int i = 0; i < 6; i++ ) {
            *pos_raw++ = *f++;
        }
    } else {
        
    }
}

void font_puts_raw(const uint8_t *font, const char *s, uint8_t *pos_raw, uint8_t bitoffset) {
    while( *s ) {
        font_put_raw(font, *s, pos_raw, bitoffset);
        s++;
        pos_raw+=6;
    }
}

void font_put(const uint8_t *font, char c, uint8_t *pos_raw) {

}
