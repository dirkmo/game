#ifndef __BUTTONS_H
#define __BUTTONS_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    BUTTON_UP      = 0x01,
    BUTTON_DOWN    = 0x02,
    BUTTON_LEFT    = 0x04,
    BUTTON_RIGHT   = 0x08,
    BUTTON_ACTION0 = 0x10,
    BUTTON_ACTION1 = 0x20,
    BUTTON_ACTION2 = 0x40,
    BUTTON_ACTION3 = 0x80,
} buttons_t;

void button_callback(uint32_t _buttons);

bool button_pressed(uint32_t button_mask);
bool button_released(uint32_t button_mask);
bool button_is_down(uint32_t button_mask);
bool button_is_up(uint32_t button_mask);

#endif
