#include "buttons.h"
#include <stdint.h>

static uint32_t s_buttons;
static uint32_t s_buttons_pressed;
static uint32_t s_buttons_released;


void buttons_callback(uint32_t _buttons) {
    if( buttons != _buttons ) {
        s_buttons_pressed |= s_buttons & 1 
        s_buttons = _buttons;
    }
}

bool button_pressed(buttons_t button) {
}

bool button_released(buttons_t button) {
}

bool button_is_down(buttons_t button) {
}

bool button_up(buttons_t button) {
}

