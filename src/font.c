#include "font.h"

void font_put_raw(char c, uint8_t *pos_raw, uint8_t bitoffset) {
    const uint8_t *bitmap = &console_font_6x8[(uint8_t)c * 8];
    uint8_t val = 0;
    if( bitoffset == 0 ) {
        for( int i = 0; i < 8; i++ ) {
            
        }
    } else {

    }
}

void font_put(char c, uint8_t *pos_raw) {

}
